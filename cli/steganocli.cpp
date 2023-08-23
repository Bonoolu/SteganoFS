#include "steganocli.h"

int SteganoCli::printUsage() {
           std:: cout <<
           "Usage: steganofs_cli <option> \n"
           "\n"
           "Options:\n"
           "  --mount <path to steganograhpic file/folder> <mount path>\n"
           "                            mounts the filesystem to the specified path\n\n"
           "  --umount <mount path>     unmounts the filesystem at the specified path\n\n"
           "  --info                    if a filesystem is mounted, shows info about the filesystem\n\n"
           "  --format <path to steganograhpic file/folder>\n"
           "                            formats a new filesystem at the specified path\n\n"
           "  --defragment <path to steganograhpic file/folder>\n"
           "                            defragments the *unmounted* filesystem at the specified path\n"
           "                            defragmenting a mounted filesystem is possible from the gui" << std::endl;
    return 0;
}

int SteganoCli::loadAndMount(const std::string& steganoPath, const std::string& mntPath) {
    // bool SteganoFsAdapter::loadFilesytemFromSteganoProvider();
    // bool SteganoFsAdapter::mount(const std::string &mntPoint)
    return 0;
}

int SteganoCli::unmountAndUnload(const std::string& mntPath) {
    // bool SteganoFsAdapter::umount()
    // bool SteganoFsAdapter::writeFilesystemToSteganoProvider()

    return 0;
}

int SteganoCli::format(const std::string& steganoPath) {
    // bool SteganoFsAdapter::createNewFilesystem(size_t diskSize);


    return 0;
}

int SteganoCli::info() {
    // getFragmentationInPercent ();
    // std::vector<size_t> getFilesystemVector ();
    // struct statfs SteganoFsAdapter::getFilesystemInfo()
    // bool SteganoFsAdapter::checkFilesystemIntegrity();
    return 0;
}

int SteganoCli::defragment(const std::string& steganoPath) {
    // bool SteganoFsAdapter::defragmentateFilesystem()
    return 0;
}

int SteganoCli::parse(int argc, char** argv) {
    if (argc >= 3) {
        std::string flag = std::string(argv[1]);
        std::string stegano_path = std::string(argv[2]);
    }
    if (argc == 4) {
        std::string flag = std::string(argv[1]);
        std::string stegano_path = std::string(argv[2]);
        std::string mount_path = std::string(argv[2]);
        if (flag == "--mount") {
            return loadAndMount(stegano_path, mount_path);
        }
    }
    return printUsage();
}

int main(int argc, char** argv) {
    SteganoCli::parse(argc, argv);
    return 0;
}
