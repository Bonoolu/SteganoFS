cmake_minimum_required(VERSION 3.5)
project(steganofs C)

set(CMAKE_C_STANDARD 99)

add_compile_options(-D_FILE_OFFSET_BITS=64)

find_package(PkgConfig REQUIRED)
pkg_search_module(FUSE REQUIRED fuse3)

add_library(steganofs steganofs.h steganofs.c hiddencluster.c hiddenfat.c hiddenfile.c ramdiskloader.c
        stegano_providers/raw/raw_provider.c
        stegano_providers/bmp/bmp_provider.c
        stegano_providers/stegano_provider.c)

# Link the FUSE library to your executable
target_link_libraries(steganofs PRIVATE ${FUSE_LIBRARIES})

# Include the FUSE header files
target_include_directories(steganofs PRIVATE ${FUSE_INCLUDE_DIRS})

install(
        TARGETS steganofs
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
)

install(
        FILES steganofs.h hiddencluster.h hiddenfat.h hiddenfile.h ramdiskloader.h
        stegano_providers/stegano_file.h
        stegano_providers/raw/raw_provider.h
        stegano_providers/bmp/bmp_provider.h
        stegano_providers/stegano_provider.h
        DESTINATION include/steganofs
)