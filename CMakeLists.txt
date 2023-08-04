cmake_minimum_required(VERSION 3.25)
project(steganoFS_C C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-D_FILE_OFFSET_BITS=64)

# Find the FUSE package and set the necessary variables
find_package(PkgConfig REQUIRED)
pkg_search_module(FUSE REQUIRED fuse3)

add_executable(steganoFS_C tests.c steganofs.h steganofs.c
        hiddenfat.h
        hiddenfat.c
        hiddenfile.c
        hiddenfile.h
        hiddencluster.c
        hiddencluster.h
        ramdiskloader.c
        ramdiskloader.h)

# Link the FUSE library to your executable
target_link_libraries(steganoFS_C PRIVATE ${FUSE_LIBRARIES})

# Include the FUSE header files
target_include_directories(steganoFS_C PRIVATE ${FUSE_INCLUDE_DIRS})