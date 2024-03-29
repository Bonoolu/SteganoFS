#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder)
    :
    m_steganoImageFolder(std::move(steganoImageFolder))
{

}

bool SteganoFsAdapter::createNewFilesystem(size_t diskSize)
{
    if (m_hiddenFat != nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem was already loaded!" << std::endl;
        return false;
    }
    m_hiddenFat = SteganoFS::steganofs_create_new_ramdisk(diskSize);
    if (m_hiddenFat) {
        std::cout << "[SteganoFS] Created new Filesystem!" << std::endl;
    }
    else {
        std::cout << "[SteganoFS] Error: Failed to create new Filesystem!" << std::endl;
    }
    return m_hiddenFat != nullptr;
}

size_t SteganoFsAdapter::formatNewFilesystem()
{
    if (m_steganoImageFolder.empty()) {
        std::cout << "[SteganoFS] Error: String passed to constructor is empty!" << std::endl;
        return 0;
    }
    size_t size = SteganoFS::steganofs_format(m_steganoImageFolder.c_str());
    if (size != 0) {
        std::cout << "[SteganoFS] Created new Filesystem of size " << size << " bytes." << std::endl;
    }
    else {
        std::cout << "[SteganoFS] Error: Failed to create new Filesystem!" << std::endl;
    }
    return size;
}

bool SteganoFsAdapter::loadFilesytemFromSteganoProvider()
{
    if (m_steganoImageFolder.empty()) {
        std::cout << "[SteganoFS] Error: String passed to constructor is empty!" << std::endl;
        return false;
    }
    try {
        if (!exists(std::filesystem::path{m_steganoImageFolder})) {
            std::cout << "[SteganoFS] Error: Could not find path: " << m_steganoImageFolder << std::endl;
            return false;
        }
    }
    catch (int e) {
        std::cout << "[SteganoFS] Error: Can not mount at: " << m_steganoImageFolder <<
                  "\nIs an orphaned SteganoFS still mounted there? Please try unmounting this path" << std::endl;
        return false;
    }
    if (m_hiddenFat != nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem was already loaded!" << std::endl;
        return false;
    }
    m_hiddenFat = SteganoFS::steganofs_load_ramdisk(m_steganoImageFolder.c_str());
    if (m_hiddenFat) {
        std::cout << "[SteganoFS] Loaded existing Filesystem!" << std::endl;
    }
    else {
        std::cout << "[SteganoFS] Error: Failed to load existing Filesystem! Maybe you need to format first."
                  << std::endl;
    }
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::mount(const std::string &mntPoint)
{
    try {
        if (!exists(std::filesystem::path{mntPoint})) {
            std::cout << "[SteganoFS] Error: Mount Path '" << mntPoint << "' does not exist!" << std::endl;
            return false;
        }
        if (!is_empty(std::filesystem::path{mntPoint})) {
            std::cout << "[SteganoFS] Error: Mount Path '" << mntPoint << "' is not empty!" << std::endl;
            return false;
        }
    }
    catch (int e) {
        std::cout << "[SteganoFS] Error: Can not mount at: " << m_steganoImageFolder <<
                  "\nIs an orphaned SteganoFS still mounted there? Please try unmounting this path" << std::endl;
        return false;
    }
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Need to load filesystem before mounting is possible!" << std::endl;
        return false;
    }
    m_mountPath = mntPoint;
    m_isMounted = true;
    bool ret = SteganoFS::steganofs_mount(m_hiddenFat, mntPoint.c_str());
    m_isMounted = false;
    if (ret) {
        std::cout << "[SteganoFS] Successfully mounted and unmounted at : " << m_mountPath << std::endl;
    }
    else {
        std::cout << "[SteganoFS] Error: Failed to mount at : " << m_mountPath << std::endl;
    }
    return ret;
}

bool SteganoFsAdapter::writeFilesystemToSteganoProvider()
{
    if (m_steganoImageFolder.empty()) {
        std::cout << "[SteganoFS] Error: String passed to constructor is empty!" << std::endl;
        return false;
    }
    try {
        if (!exists(std::filesystem::path{m_steganoImageFolder})) {
            std::cout << "[SteganoFS] Error: Could not find path: " << m_steganoImageFolder << std::endl;
            return false;
        }
    }
    catch (int e) {
        return false;
    }
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not yet loaded!" << std::endl;
        return false;
    }
    bool ret = SteganoFS::steganofs_unload_ramdisk(m_hiddenFat, m_steganoImageFolder.c_str());
    if (ret) {
        std::cout << "[SteganoFS] Successfully wrote filesystem to : " << m_steganoImageFolder << std::endl;
        m_hiddenFat = nullptr;
    }
    else {
        std::cout << "[SteganoFS] Error: Failed to write filesystem to : " << m_steganoImageFolder << std::endl;
    }
    return ret;
}

bool SteganoFsAdapter::umount(std::string path)
{
    if (path.empty()) path = m_mountPath;
    bool ret = SteganoFS::steganofs_umount(path.c_str());
    if (ret) {
        std::cout << "[SteganoFS] Successfully unmounted at : " << path << std::endl;
        m_isMounted = false;
        m_mountPath = "";
    }
    else {
        std::cout << "[SteganoFS] Failed to unmount at : " << path << std::endl;
    }
    return ret;
}

float SteganoFsAdapter::getFragmentationInPercent()
{
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not loaded yet!" << std::endl;
        return -1;
    }
    return SteganoFS::steganofs_defragmentation_percent(m_hiddenFat);
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector()
{
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't create vector! Filesystem is not loaded yet!" << std::endl;
        return {};
    }
    size_t *array = nullptr;
    size_t length = SteganoFS::steganofs_fragmentation_array(m_hiddenFat, &array);
    if (length == 0) {
        return {};
    }
    std::vector<size_t> vector(array, array + (sizeof(size_t) * length) / sizeof array[0]);
    delete (array);
    return vector;
}

bool SteganoFsAdapter::checkFilesystemIntegrity()
{
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't check integrity! Filesystem is not loaded yet!" << std::endl;
        return false;
    }
    return SteganoFS::steganofs_check_integrity(m_hiddenFat);
}

bool SteganoFsAdapter::defragmentateFilesystem()
{
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't defragment! Filesystem is not loaded yet!" << std::endl;
        return false;
    }
    SteganoFS::steganofs_defragmentate_filesystem(m_hiddenFat);
    return SteganoFS::steganofs_check_integrity(m_hiddenFat);
}

struct statvfs SteganoFsAdapter::getFilesystemInfo()
{
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Can't get Filesystem Info! Filesystem is not loaded yet!" << std::endl;
        return {};
    }
    struct statvfs stfs{};
    statvfs(m_mountPath.c_str(), &stfs);
    return stfs;
}

std::string SteganoFsAdapter::steganoImageFolder() const
{
    return m_steganoImageFolder;
}

bool SteganoFsAdapter::isMounted() const
{
    return m_isMounted;
}

bool SteganoFsAdapter::isLoaded() const
{
    return m_hiddenFat != nullptr;
}

std::string SteganoFsAdapter::mountPath() const
{
    return m_mountPath;
}

SteganoFsAdapter::~SteganoFsAdapter()
{
    if (m_hiddenFat != nullptr && m_isMounted) {
        SteganoFsAdapter::umount();
    }
    else if (m_hiddenFat != nullptr) {
        SteganoFsAdapter::writeFilesystemToSteganoProvider();
    }
}
