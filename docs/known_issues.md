## Known Issues and Limitations

SteganoFS is a work in progress and, as with any software in development, there are certain issues and limitations to be aware of. This section outlines the current known issues and limitations of the project:

1. **Memory Safety:** SteganoFS is not yet memory-safe. There is a buffer overflow vulnerability in the loading and handling of steganographic files. An attacker could modify an existing filesystem to exploit this vulnerability. This poses a risk of crashes or unauthorized access in specific scenarios.

2. **BMP Compatibility:** Currently, SteganoFS only supports hiding files within uncompressed 24-bit BMP files of version 3 without color palette information. BMP files with different configurations might not work as expected or might lead to errors.

3. **Maximal Filename Length:** Since SteganoFS is designed for usage with smaller filesystems, the maximal filename length is 29 bytes.

4. **Directories:** The Root directory can hold up to 40 files. The creation of directories is not yet implemented.

5. **Limited Filetype Support:** While SteganoFS is designed to be extendable through Stegano Providers, the project's current state restricts support to specific file types like BMP and potentially others created through custom Stegano Providers.

6. **Development Quality:** The current implementation of SteganoFS was primarily created for educational purposes. As a result, the codebase might lack the robustness and optimizations that production-ready filesystems typically have.

7. **Limited Compatibility:** SteganoFS has been developed and tested on specific Linux distributions, and its compatibility with different environments is not guaranteed.

8. **Lack of Encryption:** SteganoFS doesn't currently provide encryption for the hidden data. This means that the data hidden within the steganographic files is not protected from unauthorized access.

Please keep in mind that SteganoFS is actively being developed, and the project's maintainers are working to address these issues and improve the software's overall quality. Your feedback and contributions are valuable in identifying and mitigating these limitations.

If you encounter any problems or have suggestions for improvements, please consider contributing or reporting issues on the project's GitHub repository.