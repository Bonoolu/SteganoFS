#ifndef _STEGANOCLI_H_
#define _STEGANOCLI_H_

#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/statvfs.h>
#include "../cpp-wrapper/SteganoFsAdapter.h"

/**
 * @class SteganoCli
 * @brief Command-line interface for interacting with a steganographic filesystem.
 */
class SteganoCli
{
public:

    /**
     * @brief Prints the usage information for the command-line interface.
     * @return The exit code.
     */
    static int printUsage();

    /**
     * @brief Loads and mounts a steganographic filesystem.
     * @param steganoPath Path to the steganographic file/folder.
     * @param mntPath Path where the filesystem will be mounted.
     * @return The exit code.
     */
    static int loadAndMount(const std::string &steganoPath, const std::string &mntPath);

    /**
     * @brief Unmounts and unloads a mounted steganographic filesystem.
     * @param mntPath Path of the mounted filesystem.
     * @return The exit code.
     */
    static int unmountAndUnload(const std::string &mntPath);

    /**
     * @brief Formats a new steganographic filesystem.
     * @param steganoPath Path where the new filesystem will be created.
     * @return The exit code.
     */
    static int format(const std::string &steganoPath);

    /**
     * @brief Displays information about a steganographic filesystem.
     * @param path Path to either a mounted filesystem or a steganographic file/folder.
     * @return The exit code.
     */
    static int info(const std::string &path);

    /**
     * @brief Defragments a steganographic filesystem.
     * @param steganoPath Path to the steganographic file/folder.
     * @return The exit code.
     */
    static int defragment(const std::string &steganoPath);

    /**
     * @brief Parses command-line arguments and performs corresponding actions.
     * @param argc Number of command-line arguments.
     * @param argv Array of C-style strings containing the command-line arguments.
     * @return The exit code.
     */
    static int parse(int argc, char **argv);
};

#endif //_STEGANOCLI_H_
