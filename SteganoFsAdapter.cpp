#include "SteganoFsAdapter.h"

#include <utility>

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::loadRamdisk() {
    m_hiddenFat = createHiddenFat(5120000, 512);
}

bool SteganoFsAdapter::mount(const std::string &mntPoint) {
    return false;
}

bool SteganoFsAdapter::unloadRamdisk() {
    return false;
}

bool SteganoFsAdapter::umount(const std::string &mntPoint) {
    return false;
}


float SteganoFsAdapter::getFragmentationInPercent() {
    return 0;
}

bool SteganoFsAdapter::checkFilesystemIntegrity() {
    return false;
}

bool SteganoFsAdapter::defragmentate() {
    return false;
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
