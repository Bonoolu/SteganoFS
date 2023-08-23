#ifndef STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
#define STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H

#include <string>
#include <vector>
#include <sys/statfs.h>
#include <iostream>
#include <filesystem>
#include <utility>

namespace SteganoFS {
extern "C" {
#include "../steganofs/steganofs.h"
}
}

class SteganoFsAdapter {
 private:
  std::string m_mountPath;
  std::string m_steganoImageFolder;
  bool m_isMounted = false;
  SteganoFS::HiddenFat *m_hiddenFat = nullptr;
 public:
  explicit SteganoFsAdapter(std::string steganoImageFolder);
  ~SteganoFsAdapter();
  bool createNewFilesystem(size_t diskSize);
  bool loadFilesytemFromSteganoProvider();
  bool mount(const std::string &mntPoint);
  bool writeFilesystemToSteganoProvider();
  bool umount();
  float getFragmentationInPercent();
  std::vector<size_t> getFilesystemVector();
  bool checkFilesystemIntegrity();
  bool defragmentateFilesystem();
  struct statfs getFilesystemInfo();
  std::string steganoImageFolder() const;
  bool isMounted() const;
  bool isLoaded() const;
  std::string mountPath() const;
};

#endif //STEGANO_FS_ADAPTER_STEGANOFSADAPTER_H
