### File Compatibility Details

SteganoFS primarily utilizes BMP (Bitmap) image files for steganography. The compatibility of BMP files with SteganoFS involves specific considerations and optimizations:

- **BMP Format Requirements:** SteganoFS supports only uncompressed 24-bit BMP files with version 3 format. If a BMP image has a different format, color depth, or compression scheme, it might not be compatible with SteganoFS.

- **Header Length:** SteganoFS assumes a fixed BMP header length of exactly 54 bytes. BMP files with varying header lengths may not be recognized correctly.

- **Color Palette Information:** SteganoFS is not designed to handle BMP files with color palette information. Compatibility issues may arise when using BMP images containing color palette data.

To aid compatibility, you can use the provided Bash script to generate BMP files that adhere to SteganoFS requirements:

```bash
#!/bin/bash
# Ensure you have installed ImageMagick for this script to work

convert "$1" -define bmp:format=bmp3 \
-define bmp:colormap=0 \
-strip -alpha off \
-type truecolor -depth 24 \
-compress None \
-density 0x0 \
-endian LSB \
-units PixelsPerCentimeter \
"$2"
```

### Run-Length Encoding ###

Additionally, SteganoFS offers a Run-Length Encoding (RLE) implementation that's used for exporting filesystems without steganography but with RLE compression. This exported format is intended for modification and mounting similar to steganographic files/folders. It can be utilized by loading and writing to .steganofs files.

The provided RLE implementation code can be found in [runlengthencoding.h](../steganofs/runlengthencoding.h). This implementation allows you to encode and decode data using the RLE technique for efficient data storage and retrieval.