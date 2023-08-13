#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::formatNewRamdisk(size_t diskSize) {
    m_hiddenFat = steganofs_create_new_ramdisk(diskSize);
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::loadRamdisk() {
    m_hiddenFat = steganofs_load_ramdisk(m_steganoImageFolder.c_str());
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::mount(const std::string &mntPoint) {
    if (m_isMounted) return true;
    m_isMounted = steganofs_mount(m_hiddenFat, mntPoint.c_str());
    if (m_isMounted) m_mountPath = mntPoint;
    return m_isMounted;
}

bool SteganoFsAdapter::unloadRamdisk() {
    return steganofs_unload_ramdisk(m_hiddenFat, m_steganoImageFolder.c_str());
}

bool SteganoFsAdapter::umount() {
    return steganofs_umount(m_mountPath.c_str());
}

float SteganoFsAdapter::getFragmentationInPercent() {
    return steganofs_defragmentation_percent(m_hiddenFat);
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector() {
    size_t *array = nullptr;
    size_t length = steganofs_fragmentation_array(m_hiddenFat, &array);
    if (length == 0) {
        return {};
    }
    std::vector<size_t> vector(array, array + (sizeof(size_t) * length)  / sizeof array[0]);
    delete(array);
    return vector;
}

bool SteganoFsAdapter::checkFilesystemIntegrity() {
    return steganofs_check_integrity(m_hiddenFat);
}

bool SteganoFsAdapter::defragmentateFilesystem() {
    steganofs_defragmentate_filesystem(m_hiddenFat);
    return steganofs_check_integrity(m_hiddenFat);
}

struct statfs SteganoFsAdapter::getFilesystemInfo() {
    struct statfs stfs{};
    statfs(m_mountPath.c_str(), &stfs);
    return stfs;
}

SteganoFsAdapter::~SteganoFsAdapter() {
    if (m_hiddenFat != nullptr && m_isMounted) {
        SteganoFsAdapter::umount();
    } else if (m_hiddenFat != nullptr) {
        SteganoFsAdapter::unloadRamdisk();
    }
}
