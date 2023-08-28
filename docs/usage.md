### Usage ###

SteganoFS provides a powerful Command Line Interface (CLI) for managing your hidden filesystems. Here are the available command-line options:

```bash
# Mount the filesystem
steganofs_cli --mount /path/to/steganographic/files /mount/point

# Unmount the filesystem
steganofs_cli --umount /mount/point

# View filesystem information
steganofs_cli --info /mount/point

# Format a new filesystem
steganofs_cli --format /path/to/steganographic/files

# Defragment the filesystem
steganofs_cli --defragment /path/to/steganographic/files
```

### CLI Demo ###

Here's a basic example of a SteganoFS workflow. This example uses the example files provided with this project. Which means you can just copy and paste them and they will work.

For this example it's important to build the binaries first. Please see the [Installation Guide](install.md)

```bash
# First we make sure we are in the directory build/cli
cd build/cli

# Format a new filesystem
./steganofs_cli --format ../examples/pictures

# Mount the filesystem (this blocks until unmount)
./steganofs_cli --mount ../examples/pictures ../examples/mnt

# Perform operations on the mounted filesystem (from another terminal)
ls ../examples/mnt
cp ~/some_file ../examples/mnt

# View filesystem information (from another terminal)
./steganofs_cli --info ../examples/mnt

# Unmount the filesystem (from another terminal)
./steganofs_cli --umount  ../examples/mnt
`
# You can also get filesystem information for an unmounted
# filesystem by running --info on your steganographic files:
./steganofs_cli --info ../examples/pictures
```