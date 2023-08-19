#ifndef STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
#define STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H

#include <string>
#include <vector>
#include <sys/statfs.h>
#include <utility>


extern "C" {
    #include "../steganofs/steganofs.h"
}

class SteganoFsAdapter {
private:
    std::string m_mountPath;
    std::string m_steganoImageFolder;
    bool m_isMounted = false;
    HiddenFat *m_hiddenFat = nullptr;
public:
    explicit SteganoFsAdapter(std::string  steganoImageFolder);
    ~SteganoFsAdapter();
    bool formatNewRamdisk(size_t diskSize);
    bool loadRamdisk();
    bool mount(const std::string& mntPoint);
    bool unloadRamdisk();
    bool umount();
    float getFragmentationInPercent();
    std::vector<size_t> getFilesystemVector();
    bool checkFilesystemIntegrity();
    bool defragmentateFilesystem();
    struct statfs getFilesystemInfo();
};

#endif //STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
