#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::loadRamdisk() {
    m_hiddenFat = createHiddenFat(5120000, 512);
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
    return checkForDefragmentation(m_hiddenFat);
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector() {
    // please implement me
    showHiddenFat(m_hiddenFat, nullptr);// temporarily show filesystem
    return std::vector<size_t>();
}


bool SteganoFsAdapter::checkFilesystemIntegrity() {
    return checkIntegrity(m_hiddenFat);
}

bool SteganoFsAdapter::defragmentateFilesystem() {
    defragmentate(m_hiddenFat);
    return checkIntegrity(m_hiddenFat);
}

struct statfs SteganoFsAdapter::getFilesystemInfo() {
    struct statfs stfs{};
    statfs(m_mountPath.c_str(), &stfs);
    return stfs;
}

SteganoFsAdapter::~SteganoFsAdapter() {
    if (m_hiddenFat != nullptr) {
        freeHiddenFat(m_hiddenFat);
    }
}
