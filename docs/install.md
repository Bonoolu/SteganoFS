### Installation Guide

To install SteganoFS and its dependencies, follow these steps:

1. **Linux OS:** Ensure you are using a 64-bit Linux operating system.

2. **Install Dependencies:**

    - **fuse3:** Install the fuse3 library using your package manager.

      ```bash
      sudo apt-get install libfuse3-dev   # For Debian/Ubuntu
      ```

    - **Qt5:** If you plan to use the Graphical User Interface (GUI), you'll need Qt5. Install it using your package manager. Installing qtcreator should pull all nessesary packages.

      ```bash
      sudo apt-get install qtcreator   # For Debian/Ubuntu
      ```

3. **Clone the Repository:**

    ```bash
    git clone https://github.com/yourusername/steganofs.git
    cd steganofs
    ```
   
4. **Build the Project:**

    ```bash
    mkdir build 
    cd build
    cmake ..
    make
   ```
   
Done. You can now head to the [Usage Guide](./usage.md) to try out SteganoFS!
