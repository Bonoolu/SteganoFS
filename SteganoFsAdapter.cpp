#include "SteganoFsAdapter.h"

SteganoFsAdapter::SteganoFsAdapter(std::string steganoImageFolder) :
m_steganoImageFolder(std::move(steganoImageFolder)){

}

bool SteganoFsAdapter::createNewFilesystem(size_t diskSize) {
    if (m_hiddenFat != nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem was already loaded!" << std::endl;
        return false;
    }
    m_hiddenFat = (HiddenFat*) 1234; // Here we would normally create a brand new HiddenFat
    std::cout << "[SteganoFS] Created new Filesystem!" << std::endl;
    return true;
}

bool SteganoFsAdapter::loadFilesystemFromSteganoProvider() {
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
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(m_steganoImageFolder);
    bool found_bmp_or_bin = std::any_of(begin(iterator), end(iterator), [] (const std::filesystem::directory_entry& entry) {
        if (!exists(entry.path()) && entry.path().filename().string().empty()) {
            return false;
        }
        std::string filename = entry.path().filename().string();
        if (filename.length() < 4) {
            return false;
        }
        if (filename.substr(filename.find_last_of('.') + 1) == "bmp" ||
            filename.substr(filename.find_last_of('.') + 1) == "bin" ||
            filename.substr(filename.find_last_of('.') + 1) == "BMP" ||
            filename.substr(filename.find_last_of('.') + 1) == "BIN") {
            return true;
        }
        return false;
    });
    if (!found_bmp_or_bin) {
        std::cout << "[SteganoFS] Error: Could not find any BMP or BIN files in path: " << m_steganoImageFolder << std::endl;
        return false;
    }
    m_hiddenFat = (HiddenFat*) 1234;
    std::cout << "[SteganoFS] Loaded Filesystem successfully! " << m_steganoImageFolder << std::endl;
    return true;
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
    m_isMounted = true;
    m_mountPath = mntPoint;
    std::cout << "[SteganoFS] Successfully mounted at : " << m_mountPath << std::endl;
    return m_isMounted;
}

bool SteganoFsAdapter::writeFilesystemToSteganoProvider() {
    if (m_isMounted) {
        std::cout << "[SteganoFS] Error: Can't write a mounted filesystem! unmount first!" << std::endl;
        return false;
    }
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
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(m_steganoImageFolder);
    bool found_bmp_or_bin = std::any_of(begin(iterator), end(iterator), [] (const std::filesystem::directory_entry& entry) {
        if (!exists(entry.path()) && entry.path().filename().string().empty()) {
            return false;
        }
        std::string filename = entry.path().filename().string();
        if (filename.length() < 4) {
            return false;
        }
        if (filename.substr(filename.find_last_of('.') + 1) == "bmp" ||
            filename.substr(filename.find_last_of('.') + 1) == "bin" ||
            filename.substr(filename.find_last_of('.') + 1) == "BMP" ||
            filename.substr(filename.find_last_of('.') + 1) == "BIN") {
            return true;
        }
        return false;
    });
    if (!found_bmp_or_bin) {
        std::cout << "[SteganoFS] Error: Could not find any BMP or BIN files in path: " << m_steganoImageFolder << std::endl;
        return false;
    }
    m_hiddenFat = nullptr;
    std::cout << "[SteganoFS] Successfully wrote fileystem to disk! " << m_steganoImageFolder << std::endl;
    return true;
}

bool SteganoFsAdapter::umount() {
    if (!m_isMounted) {
        std::cout << "[SteganoFS] Error: Filesystem is not mounted yet!" << std::endl;
        return false;
    }
    m_isMounted = false;
    std::cout << "[SteganoFS] Successfully unmounted at : " << m_mountPath << std::endl;
    m_mountPath = "";
    return true;
}

float SteganoFsAdapter::getFragmentationInPercent() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not loaded yet!" << std::endl;
        return -1;
    }
    return fragmentation;
}

std::vector<size_t> SteganoFsAdapter::getFilesystemVector() {
    if (m_hiddenFat == nullptr) {
        std::cout << "[SteganoFS] Error: Filesystem is not loaded yet!" << std::endl;
        return {};
    }
    std::vector<size_t> v(32);
    std::iota (std::begin(v), std::end(v), 1);
    for (size_t i = 0; i < 32; i++) v.push_back(0);
    if (fragmentation == 0) {
        return v;
    }
    auto rng = std::default_random_engine {};
    std::shuffle(v.begin(), v.end(), rng);
    return v;

}

bool SteganoFsAdapter::checkFilesystemIntegrity() {
    return true;
}

bool SteganoFsAdapter::defragmentateFilesystem() {
    fragmentation = 0;
    return true;
}

struct SteganoFsAdapter::statvfs SteganoFsAdapter::getFilesystemInfo() {
    struct SteganoFsAdapter::statvfs stbuf{
            .f_bsize = 512,   // Filesystem block size
            .f_frsize = 512,  // Fundamental filesystem block size
            .f_blocks = 64,   // Total data blocks in filesystem
            .f_bfree = 32,   // Free blocks
            .f_bavail = 32,  // Free blocks available to non-superuser
            .f_namemax = 11
    };
    return stbuf;
}

SteganoFsAdapter::~SteganoFsAdapter() {
    if (m_hiddenFat != nullptr && m_isMounted) {
        SteganoFsAdapter::umount();
    } else if (m_hiddenFat != nullptr) {
        SteganoFsAdapter::writeFilesystemToSteganoProvider();
    }
}
