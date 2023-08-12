#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::loadRamdisk() {
    m_hiddenFat = steganofs_load_ramdisk(m_steganoImageFolder.c_str());
    return m_hiddenFat != nullptr;
}

bool SteganoFsAdapter::mount(const std::string &mntPoint) {
    // please implement me
    return false;
}

bool SteganoFsAdapter::unloadRamdisk() {
    // please implement me
    return false;
}

bool SteganoFsAdapter::umount() {
    // please implement me
    return false;
}

float SteganoFsAdapter::getFragmentationInPercent() {
    return steganofs_defragmentation_percent(m_hiddenFat);
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector() {
    // please implement me properly
    steganofs_show_fragmentation(m_hiddenFat, nullptr);
    return std::vector<size_t>();
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
