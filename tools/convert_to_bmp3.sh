#!/bin/bash
# you need to install ffmpeg for this to work

convert "$1" -define bmp:format=bmp3 \
-define bmp:colormap=0 \
-strip -alpha off \
-type truecolor -depth 24 \
-compress None \
-density 0x0 \
-endian LSB \
-units PixelsPerCentimeter \
"$2"

# actually, most of these flags are redundant, it's already plenty to convert like this:
# convert "$1" -define bmp:format=bmp3 -type truecolor "$2"