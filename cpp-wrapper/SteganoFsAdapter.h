#ifndef STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
#define STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H

#include <string>
#include <vector>
#include <sys/statvfs.h>
#include <iostream>
#include <filesystem>
#include <utility>

namespace SteganoFS
{
extern "C" {
#include "../steganofs/steganofs.h"
}
}

/**
 * @class SteganoFsAdapter
 * @brief Adapter class for interacting with the SteganoFS filesystem.
 */
class SteganoFsAdapter {
 private:
  std::string m_mountPath; /**< Mount path for the filesystem. */
  std::string m_steganoImageFolder; /**< Path to the stegano image folder. */
  bool m_isMounted = false; /**< Indicates if the filesystem is mounted. */
  SteganoFS::HiddenFat *m_hiddenFat = nullptr; /**< Pointer to the HiddenFat instance. */
 public:

  /**
   * @brief Constructor for SteganoFsAdapter.
   * @param steganoImageFolder Path to the stegano image folder.
   */
  explicit SteganoFsAdapter (std::string steganoImageFolder);

  /**
   * @brief Destructor for SteganoFsAdapter.
   */
  ~SteganoFsAdapter ();

  /**
   * @brief Creates a new filesystem the specified path of steganographic files.
   * @return The size of the new filesystem. 0 if fails.
   */
  size_t formatNewFilesystem ();

  /**
   * @brief Creates a new filesystem with the given disk size.
   * @param diskSize Size of the disk in bytes.
   * @return True if successful, false otherwise.
   */
  bool createNewFilesystem (size_t diskSize);

  /**
   * @brief Load the hidden filesystem from the steganographic image provider.
   * @return True if the filesystem was loaded successfully, false otherwise.
   */
  bool loadFilesytemFromSteganoProvider ();

  /**
   * @brief Mount the hidden filesystem to the given mount point.
   * @param mntPoint Mount point for the filesystem.
   * @return True if the filesystem was mounted successfully, false otherwise.
   */
  bool mount (const std::string &mntPoint);

  /**
   * @brief Write the hidden filesystem back to the steganographic image provider.
   * @return True if the filesystem was written successfully, false otherwise.
   */
  bool writeFilesystemToSteganoProvider ();

  /**
   * @brief Unmount the hidden filesystem.
   * @param mntPoint Mount point for the filesystem. Can be omitted if set as member
   * @return True if the filesystem was unmounted successfully, false otherwise.
   */
  bool umount (std::string mntPoint = "");

  /**
   * @brief Get the fragmentation of the hidden filesystem in percentage.
   * @return Fragmentation percentage if the filesystem is loaded, otherwise -1.
   */
  float getFragmentationInPercent ();

  /**
   * @brief Get a vector containing fragmentation information of the filesystem.
   * @return Vector of fragmentation data if the filesystem is loaded, otherwise an empty vector.
   */
  std::vector<size_t> getFilesystemVector ();

  /**
   * @brief Check the integrity of the hidden filesystem.
   * @return True if the filesystem is intact, false if integrity check fails.
   */
  bool checkFilesystemIntegrity ();

  /**
   * @brief Defragment the hidden filesystem.
   * @return True if defragmentation was successful, false otherwise.
   */
  bool defragmentateFilesystem ();

  /**
   * @brief Get information about the hidden filesystem.
   * @return Structure containing filesystem information.
   */
  struct statvfs getFilesystemInfo ();

  /**
   * @brief Get the steganographic image folder path.
   * @return Steganographic image folder path.
   */
  std::string steganoImageFolder () const;

  /**
   * @brief Check if the filesystem is mounted.
   * @return True if the filesystem is mounted, false otherwise.
   */
  bool isMounted () const;

  /**
   * @brief Check if the filesystem is loaded.
   * @return True if the filesystem is loaded, false otherwise.
   */
  bool isLoaded () const;

  /**
   * @brief Get the mount path of the filesystem.
   * @return Mount path of the filesystem.
   */
  std::string mountPath () const;
};

#endif //STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
