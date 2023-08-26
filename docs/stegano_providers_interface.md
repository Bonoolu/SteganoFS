### Stegano Providers Interface Documentation

Stegano Providers are essential for extending SteganoFS's capabilities to different file types. To create a new Stegano Provider, follow these steps:

1. **Create Provider Folder:** Inside the `stegano_providers` directory, create a new folder for your provider, e.g., `pdf`.

2. **Implement Functions:** In your provider folder, create header and source files for your provider.

```c
struct SteganoFile read_pdf(const char *path);
size_t write_pdf(struct SteganoFile);
```

3. **Register Provider:** In `stegano_provider.c`, import your provider header and add it to the `providers` struct array.

4. **Test Your Provider:** Create a test suite for your provider in the `test` directory.


### Subprocess Provider Guide

The Subprocess Provider feature allows you to integrate steganographic techniques from various languages. You can spawn subprocesses from provider code. Here's a basic example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct SteganoFile read_custom(const char *path) {
    // Spawn a subprocess using a system command
    char command[256];
    snprintf(command, sizeof(command), "python3 steganographic_script.py %s", path);

    FILE *fp = popen(command, "r");
    if (!fp) {
        // Handle error
    }

    // Read data from the subprocess
    char buffer[4096];
    size_t read_bytes = fread(buffer, 1, sizeof(buffer), fp);

    pclose(fp);

    // Populate SteganoFile structure
    struct SteganoFile result;
    result.payload = malloc(read_bytes);
    memcpy(result.payload, buffer, read_bytes);
    result.payload_size = read_bytes;

    return result;
}
```