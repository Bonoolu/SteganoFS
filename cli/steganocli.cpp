#include "steganocli.h"

int SteganoCli::printUsage()
{
    std::cout <<
              "Usage: steganofs_cli <option> \n"
              "\n"
              "Options:\n"
              "  --mount <path to steganograhpic file/folder> <mount path>\n"
              "                            mounts the filesystem to the specified path\n\n"
              "  --umount <mount path>     unmounts the filesystem at the specified path\n\n"
              "  --info <mount path> or <path to steganograhpic file/folder>\n"
              "                            shows info about the filesystem\n\n"
              "  --format <path to steganograhpic file/folder>\n"
              "                            formats a new filesystem at the specified path\n\n"
              "  --defragment <path to steganograhpic file/folder>\n"
              "                            defragments the *unmounted* filesystem at the specified path\n"
              "                            defragmenting a mounted filesystem is possible from the gui\n\n"
              "  --help                    shows this message"<< std::endl;
    return 0;
}

int SteganoCli::loadAndMount(const std::string &steganoPath, const std::string &mntPath)
{
    auto *steganoFsAdapter = new SteganoFsAdapter(steganoPath);
    bool ret = steganoFsAdapter->loadFilesytemFromSteganoProvider();
    if (!ret) {
        return -1;
    }
    ret = steganoFsAdapter->mount(mntPath);
    if (!ret) {
        return -1;
    }
    ret = steganoFsAdapter->writeFilesystemToSteganoProvider();
    if (!ret) {
        return -1;
    }
    delete (steganoFsAdapter);
    return 0;
}

int SteganoCli::unmountAndUnload(const std::string &mntPath)
{
    auto *steganoFsAdapter = new SteganoFsAdapter("");
    bool ret = steganoFsAdapter->umount(mntPath);
    if (!ret) {
        return -1;
    }
    delete (steganoFsAdapter);
    return 0;
}

int SteganoCli::format(const std::string &steganoPath)
{
    auto *steganoFsAdapter = new SteganoFsAdapter(steganoPath);
    size_t size = steganoFsAdapter->formatNewFilesystem();
    delete (steganoFsAdapter);
    if (size != 0)
        return 0;
    else
        return -1;
}

int SteganoCli::info(const std::string &path)
{
    struct statvfs parentFsStat{}, childFsStat{};
    if (statvfs(path.c_str(), &childFsStat) != 0) {
        return -1;
    }

    char *originalCwd;
    size_t cwdSize = pathconf(".", _PC_PATH_MAX);
    if ((originalCwd = (char *) malloc((size_t) cwdSize)) != nullptr) { // see free() below
        if (getcwd(originalCwd, cwdSize) == nullptr) {
            free(originalCwd);
            return -1;
        }
    }
    else {
        free(originalCwd);
        return -1;
    }

    if (chdir(path.c_str()) != 0) {
        free(originalCwd);
        return -1;
    }

    if (statvfs("..", &parentFsStat) != 0) {
    }

    if (childFsStat.f_fsid != parentFsStat.f_fsid) {
        std::cout << "Filesystem Info:\n"
                     "Filesystem block size:                    " << childFsStat.f_bsize << "\n" <<
                  "Fundamental filesystem block size:        " << childFsStat.f_frsize << "\n" <<
                  "Total data blocks in filesystem:          " << childFsStat.f_blocks << "\n" <<
                  "Free blocks:                              " << childFsStat.f_bfree << "\n" <<
                  "Free blocks available to non-superuser:   " << childFsStat.f_bavail << "\n" <<
                  "Maximum filename length:                  " << childFsStat.f_namemax << std::endl;
        free(originalCwd);
        return 0;
    }
    else {
        chdir(originalCwd);
        free(originalCwd);
        auto *steganoFsAdapter = new SteganoFsAdapter(path);
        bool ret = steganoFsAdapter->loadFilesytemFromSteganoProvider();
        if (!ret) {
            return -1;
        }
        float fragmentationInPercent = steganoFsAdapter->getFragmentationInPercent();
        bool integrity = steganoFsAdapter->checkFilesystemIntegrity();
        delete (steganoFsAdapter);
        std::cout << "Filesystem Info:\n"
                     "Integrity check:                          " << (integrity ? "true" : "false") << "\n" <<
                  "Fragmentation in percent:                    " << int(fragmentationInPercent) << std::endl;

    }
    return 0;
}

int SteganoCli::defragment(const std::string &steganoPath)
{
    auto *steganoFsAdapter = new SteganoFsAdapter(steganoPath);
    bool ret = steganoFsAdapter->loadFilesytemFromSteganoProvider();
    if (!ret) {
        return -1;
    }
    ret = steganoFsAdapter->defragmentateFilesystem();
    if (!ret) {
        return -1;
    }
    delete (steganoFsAdapter);
    return 0;
}

int SteganoCli::parse(int argc, char **argv)
{
    if (argc >= 3) {
        std::string flag = std::string(argv[1]);
        std::string steganoPath = std::string(argv[2]);
        if (flag == "--format") {
            return format(steganoPath);
        }
        if (flag == "--defragment") {
            return defragment(steganoPath);
        }
        if (flag == "--info") {
            return info(steganoPath);
        }
        if (flag == "--umount" || flag == "--unmount") {
            return unmountAndUnload(steganoPath);
        }
    }
    if (argc == 4) {
        std::string flag = std::string(argv[1]);
        std::string steganoPath = std::string(argv[2]);
        std::string mountPath = std::string(argv[3]);
        if (flag == "--mount") {
            return loadAndMount(steganoPath, mountPath);
        }
    }
    return printUsage();
}

int main(int argc, char **argv)
{
    SteganoCli::parse(argc, argv);
    return 0;
}
