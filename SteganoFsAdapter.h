#ifndef STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
#define STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H

#include <vector>
#include <filesystem>
#include <random>
#include <algorithm>
#include <numeric>
#include <iostream>

class SteganoFsAdapter {
private:
    struct HiddenFat {
        int this_is_just_a_dummy;
    };
    std::string m_mountPath;
    std::string m_steganoImageFolder;
    bool m_isMounted = false;
    HiddenFat *m_hiddenFat = nullptr;
    float fragmentation = 74.23;
public:
    struct statvfs
    {
        unsigned long int f_bsize;
        unsigned long int f_frsize;
        __fsblkcnt_t f_blocks;
        __fsblkcnt_t f_bfree;
        __fsblkcnt_t f_bavail;
        unsigned long int f_namemax;
    };
    explicit SteganoFsAdapter(std::string  steganoImageFolder);
    ~SteganoFsAdapter();
    bool createNewFilesystem(size_t diskSize);
    bool loadFilesystemFromSteganoProvider();
    bool mount(const std::string& mntPoint);
    bool writeFilesystemToSteganoProvider();
    bool umount();
    float getFragmentationInPercent();
    std::vector<size_t> getFilesystemVector();
    bool checkFilesystemIntegrity();
    bool defragmentateFilesystem();
    struct SteganoFsAdapter::statvfs getFilesystemInfo();
};

#endif //STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
