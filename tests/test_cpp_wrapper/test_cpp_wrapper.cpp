/**
 * @file test_cpp_wrapper.cpp
 * @brief This file contains a test suite for the SteganoFsAdapter class.
 */

#include <iostream>
#include "../../cpp-wrapper/SteganoFsAdapter.h"

/**
 * @brief The main entry point for the test suite.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of pointers to command-line arguments.
 * @return 0 on successful execution.
 */

int main (int argc, char **argv)
{
  SteganoFsAdapter steganoFsAdapter ("test_cpp_wrapper.steganofs");
  bool status = steganoFsAdapter.loadFilesytemFromSteganoProvider ();
  if (!status)
    {
      std::cout << "Loading Ramdisk failed!" << std::endl;
    }
  std::vector<size_t> vector = steganoFsAdapter.getFilesystemVector ();
  if (vector.empty ())
    {
      std::cout << "Getting Filesystemvector failed, is empty!" << std::endl;
    }
  std::cout << "Got Filesystem vector:\n";
  for (size_t v : vector)
    {
      std::cout << v << ", ";
    }
  std::cout << std::endl;
  std::cout << "Defragmenting:" << std::endl;
  steganoFsAdapter.defragmentateFilesystem ();

  vector = steganoFsAdapter.getFilesystemVector ();
  if (vector.empty ())
    {
      std::cout << "Getting Filesystemvector failed, is empty!" << std::endl;
    }
  std::cout << "Got Filesystem vector:\n";
  for (size_t v : vector)
    {
      std::cout << v << ", ";
    }
  std::cout << std::endl;


//    status = steganoFsAdapter.mount("test_mnt");
//    if (!status) {
//        std::cout << "Mounting to test_mnt failed!" << std::endl;
//    }
//    status = steganoFsAdapter.umount();
//    if (!status) {
//        std::cout << "Unmounting to test_mnt failed!" << std::endl;
//    }
//    status = steganoFsAdapter.writeFilesystemToSteganoProvider();
//    if (!status) {
//        std::cout << "Unloading Ramdisk failed!" << std::endl;
//    }
  return 0;
}
