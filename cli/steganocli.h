#ifndef _STEGANOCLI_H_
#define _STEGANOCLI_H_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/statvfs.h>
#include "../cpp-wrapper/SteganoFsAdapter.h"

class SteganoCli
{
public:
    static int printUsage();
    static int loadAndMount(const std::string &steganoPath, const std::string &mntPath);
    static int unmountAndUnload(const std::string &mntPath);
    static int format(const std::string &steganoPath);
    static int info(const std::string &path);
    static int defragment(const std::string &steganoPath);
    static int parse(int argc, char **argv);
};

#endif //_STEGANOCLI_H_
