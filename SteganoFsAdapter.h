#ifndef STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
#define STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H

#include <string>
#include <sys/statfs.h>
#include "steganofs/steganofs.h"

class SteganoFsAdapter {
private:
    std::string m_mountPath;
    std::string m_steganoImageFolder;
    bool m_isMounted = false;
    HiddenFat *m_hiddenFat = nullptr;
public:
    SteganoFsAdapter(std::string  steganoImageFolder);
    ~SteganoFsAdapter();
    bool loadRamdisk();
    bool mount(const std::string& mntPoint);
    bool unloadRamdisk();
    bool umount(const std::string& mntPoint);
    float getFragmentationInPercent();
    bool checkFilesystemIntegrity();
    bool defragmentate();
    struct statfs getFilesystemInfo();
};

#endif //STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
