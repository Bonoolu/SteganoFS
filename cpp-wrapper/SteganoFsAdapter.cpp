#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::createNewFilesystem(size_t diskSize) {
    if (m_hiddenFat != nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem was already loaded!" << std::endl;
        return false;
    }
    m_hiddenFat = SteganoFS::steganofs_create_new_ramdisk(diskSize);
    if (m_hiddenFat) {
        std::cout << "[SteganoFS] Created new Filesystem!" << std::endl;
    } else {
        std::cout << "[SteganoFS] Error: Failed to create new Filesystem!" << std::endl;
    }
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::loadFilesytemFromSteganoProvider() {
    if (m_steganoImageFolder.empty()) {
        std::cout << "[SteganoFS] Error: String passed to constructor is empty!" << std::endl;
        return false;
    }
    if (!exists(std::filesystem::path{m_steganoImageFolder})) {
        std::cout << "[SteganoFS] Error: Could not find path: " << m_steganoImageFolder << std::endl;
        return false;
    }
    if (m_hiddenFat != nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem was already loaded!" << std::endl;
        return false;
    }
    m_hiddenFat = SteganoFS::steganofs_load_ramdisk(m_steganoImageFolder.c_str());
    if (m_hiddenFat) {
        std::cout << "[SteganoFS] Loaded existing Filesystem!" << std::endl;
    } else {
        std::cout << "[SteganoFS] Error: Failed to load existing Filesystem!" << std::endl;
    }
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::mount(const std::string &mntPoint) {
    if (m_isMounted) {
        std::cout << "[SteganoFS] Error: Filesystem is already mounted!" << std::endl;
        return false;
    }
    if (!exists(std::filesystem::path{mntPoint})) {
        std::cout << "[SteganoFS] Error: Mount Path '" << mntPoint << "' does not exist!" << std::endl;
        return false;
    }
    if (!is_empty(std::filesystem::path{mntPoint})) {
        std::cout << "[SteganoFS] Error: Mount Path '" << mntPoint << "' is not empty!" << std::endl;
        return false;
    }
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Need to load filesystem before mounting is possible!" << std::endl;
        return false;
    }
    m_isMounted = SteganoFS::steganofs_mount(m_hiddenFat, mntPoint.c_str());
    if (m_isMounted) {
        m_mountPath = mntPoint;
        std::cout << "[SteganoFS] Successfully mounted at : " << m_mountPath << std::endl;
    } else {
        std::cout << "[SteganoFS] Error: Failed to mount at : " << m_mountPath << std::endl;
    }
    return m_isMounted;
}

bool SteganoFsAdapter::writeFilesystemToSteganoProvider() {
    if (m_steganoImageFolder.empty()) {
        std::cout << "[SteganoFS] Error: String passed to constructor is empty!" << std::endl;
        return false;
    }
    if (!exists(std::filesystem::path{m_steganoImageFolder})) {
        std::cout << "[SteganoFS] Error: Could not find path: " << m_steganoImageFolder << std::endl;
        return false;
    }
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not yet loaded!" << std::endl;
        return false;
    }
    bool ret = SteganoFS::steganofs_unload_ramdisk(m_hiddenFat, m_steganoImageFolder.c_str());
    if (ret) {
        std::cout << "[SteganoFS] Successfully wrote filesystem to : " << m_steganoImageFolder << std::endl;
    } else {
        std::cout << "[SteganoFS] Error: Failed to write filesystem to : " << m_steganoImageFolder << std::endl;
    }
    return ret;
}

bool SteganoFsAdapter::umount() {
    if (!m_isMounted) {
        std::cout << "[SteganoFS] Error: Filesystem is not mounted yet!" << std::endl;
        return false;
    }
    bool ret = SteganoFS::steganofs_umount(m_mountPath.c_str());
    if (ret) {
        std::cout << "[SteganoFS] Successfully unmounted at : " << m_mountPath << std::endl;
        m_isMounted = false;
        m_mountPath = "";
    } else {
        std::cout << "[SteganoFS] Failed to unmount at : " << m_mountPath << std::endl;
    }
    return ret;
}

float SteganoFsAdapter::getFragmentationInPercent() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not loaded yet!" << std::endl;
        return -1;
    }
    return SteganoFS::steganofs_defragmentation_percent(m_hiddenFat);
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't create vector! Filesystem is not loaded yet!" << std::endl;
        return {};
    }
    size_t *array = nullptr;
    size_t length = SteganoFS::steganofs_fragmentation_array(m_hiddenFat, &array);
    if (length == 0) {
        return {};
    }
    std::vector<size_t> vector(array, array + (sizeof(size_t) * length)  / sizeof array[0]);
    delete(array);
    return vector;
}

bool SteganoFsAdapter::checkFilesystemIntegrity() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't check integrity! Filesystem is not loaded yet!" << std::endl;
        return false;
    }
    return SteganoFS::steganofs_check_integrity(m_hiddenFat);
}

bool SteganoFsAdapter::defragmentateFilesystem() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't defragment! Filesystem is not loaded yet!" << std::endl;
        return false;
    }
    SteganoFS::steganofs_defragmentate_filesystem(m_hiddenFat);
    return SteganoFS::steganofs_check_integrity(m_hiddenFat);
}

struct statfs SteganoFsAdapter::getFilesystemInfo() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't get Filesystem Info! Filesystem is not loaded yet!" << std::endl;
        return {};
    }
    struct statfs stfs{};
    statfs(m_mountPath.c_str(), &stfs);
    return stfs;
}

SteganoFsAdapter::~SteganoFsAdapter() {
//    if (m_hiddenFat != nullptr && m_isMounted) {
//        SteganoFsAdapter::umount();
//    } else if (m_hiddenFat != nullptr) {
//        SteganoFsAdapter::writeFilesystemToSteganoProvider();
//    }
}
