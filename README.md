# SteganoFS

![test_suit_workflow](https://github.com/Bonoolu/SteganoFS/actions/workflows/testsuit.yml/badge.svg)

SteganoFS is a developing project designed to explore the concept of concealing an entire mountable filesystem within steganographic files. The project has reached a functional state, demonstrating its potential capabilities. However, it's important to note that while it functions, it's still in the developmental phase and not recommended for practical data security purposes at this stage.

<!-- ![SteganoFS Demo](link_to_demo_image.png) -->

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation and Dependencies](#installation-and-dependencies)
- [Usage](#usage)
- [GUI: Pluto Explorer](#gui-pluto-explorer)
- [Contributing](#contributing)
- [Architecture](#architecture)
- [Stegano Providers Interface](#stegano-providers-interface)
- [Subprocess Provider](#subprocess-provider)
- [Library Interfaces](#library-interfaces)
- [Test Suit](#test-suit)
- [File Compatibility](#file-compatibility)
- [Documentation](#documentation)
- [Known Issues and Limitations](#known-issues-and-limitations)
- [License](#license)
- [Contact and Support](#contact-and-support)

## Introduction

SteganoFS offers a solution for securely hiding files in a hostile environment, utilizing steganographic image files, primarily BMP files. A Developer Interface allows to add support for additional file types.

## Features

- Conceal an entire mountable filesystem within steganographic files.
- Extend functionality through the Developer Interface to support additional file types.
- Compatible with Linux operating systems, utilizing fuse3 technology.
- Includes both a Command Line Interface (CLI) and a Graphical User Interface (GUI).

## Installation and Dependencies

To use SteganoFS, you need a Linux operating system and the fuse3 library. The CLI requires the SteganoFS library, while the GUI necessitates Qt5 and the SteganoFS library. Detailed installation instructions can be found in the [Installation Guide](./docs/install.md).

## Usage

To effectively use SteganoFS, familiarize yourself with the available command-line options. You can find detailed information in the [Usage Guide](./docs/usage.md). Here's a quick example of a typical workflow:

```bash
#Format a new filesystem
steganofs_cli --format /path/to/steganographic/files

#Mount the filesystem
steganofs_cli --mount /path/to/steganographic/files /mount/point

#Perform operations on the mounted filesystem
ls /mount/point
cp ~/some_file /mount/point

#View filesystem information
steganofs_cli --info /mount/point

#Unmount the filesystem from a different terminal
steganofs_cli --umount /mount/point
```

## GUI: Pluto Explorer
The Pluto Explorer is a Graphical User Interface (GUI) used for **interacting with concealed filesystems within steganographic image files through the SteganoFS system**. Built using C++ and the Qt framework, it resembles Windows File Explorer and offers easy navigation. It includes features like a Tree View for hierarchy, a Path Input Field for quick navigation, and Back/Forward Buttons for location history. The GUI has functional buttons for Previewing files, switching to Light Mode, and upcoming functions like Paste, Delete, Cut, Copy, New Folder, and New File. It enables **mounting** of concealed filesystems from steganographic images, providing options for interacting with the files, viewing **filesystem information**, assessing the **fragmentation status** and **defragmenting the selected filesystem**, **formatting** the filesystem, and **unmounting** it for controlled access.
You can find a more detailed description in the [GUI Documentation](./docs/gui_pluto_explorer.md)

## Contributing

SteganoFS welcomes contributions from the community. We particularly seek new Stegano Providers for additional file types.

## Architecture

SteganoFS comprises several essential components, including fuse3 for mounting, the filesystem implementation, steganographic providers, and the ramdiskloader. For a detailed overview of the project's architecture, see the [Architecture Guide](./docs/architecture.md).

## Stegano Providers Interface

Stegano Providers are fundamental to SteganoFS's versatility. To implement a new Stegano Provider, follow the guidelines provided in the [Stegano Providers Interface Documentation](./docs/stegano_providers_interface.md). The documentation includes an examples for PDF and subprocess providers.

## Subprocess Provider

The Subprocess Provider pattern allows you to spawn subprocesses from provider code, enabling integration of steganographic techniques in various languages. For an example and instructions, refer to the [Subprocess Provider Guide](../docs/stegano_providers_interface.md#subprocess-provider).

## Library Interfaces ##

- **C Interface Documentation:** For C enthusiasts, we've documented the [steganofs.h Documentation](doxygen/c/steganofs.md) that defines the C interface of SteganoFS. This interface grants you direct access to SteganoFS functionality within your C projects.

- **C++ Interface Documentation:** Check out the [SteganoFsAdapter.h Documentation](doxygen/cpp/doxygen.md#class-SteganoFsAdapter) to see how you can seamlessly incorporate SteganoFS into your C++ projects. The C++ interface provides a user-friendly wrapper around the core functionality of SteganoFS.

## Test Suite

SteganoFS comes equipped with a comprehensive test suite designed to ensure the reliability and functionality of its core components. This test suite covers a wide range of scenarios and functions, including filesystem behavior, RAM disk loader functionality, run-length encoding, and steganography.

For detailed information about the types of tests available, how to run them, and how to contribute additional tests, please refer to the [Test Suite Documentation](./docs/tests.md). This documentation provides insights into the structure of the test suite, running tests, and guidelines for creating new tests.

## File Compatibility

Learn about BMP file compatibility, RLE implementation, and exporting the filesystem without steganography in the [File Compatibility Details](./docs/compatibility.md) section.

## Documentation

For more in-depth information, browse the [Documentation](./docs/) folder. It includes detailed documentation on the Stegano Provider interface, C and C++ interfaces, and other technical aspects.

## Known Issues and Limitations

SteganoFS is in early development and not memory-safe. As such, it's recommended for educational and experimental purposes only. Read more about known issues and limitations in the [Known Issues Guide](./docs/known_issues.md).

## License

SteganoFS is open-source software released under the [GNU General Public License version 3 (GPL-3.0)](./LICENSE).

## Contact and Support

For questions, support, or to get involved, reach out to us at [henry-h@cks-the-pla.net](mailto:henry-h@cks-the-pla.net).
