#!/bin/bash

inPath=$1
outPath=$2

gcc tile.c ../Image_IO/RasterImage.c ../Image_IO/imageIO_TGA.c -lm -o tile

shopt -s nullglob
fileArr=($inPath*)


# for i in "${fileArr[@]}"
# do
#     for ((j=0; j<${#i}; j++)); do
#         if [ "${i:$j:1}" == "." ]; then
#             numidx="$(($j-2))"
#             echo "${i:$numidx:2}"
#         fi
#     done
# done

