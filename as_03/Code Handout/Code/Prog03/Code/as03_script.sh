#!/bin/bash

echo $1
echo $2

imageFilePath=$1
outPath=$2

gcc dimensions.c ImageIO/imageIO_TGA.c helperFuncs.c -o dimensions
gcc rotate.c ImageIO/imageIO_TGA.c helperFuncs.c -o rotate
gcc split.c ImageIO/imageIO_TGA.c helperFuncs.c -o split
gcc cropping.c ImageIO/imageIO_TGA.c helperFuncs.c -o crop

height=$(./dimensions -h "$imageFilePath")
width=$(./dimensions -w "$imageFilePath")

middleH=$(($height/2))
middleW=$(($width/2))


./crop 0 $middleH $middleW $middleH $imageFilePath $outPath
./crop $middleW 0 $middleW $middleH $imageFilePath $outPath
./crop $middleW $middleH $middleW $middleH $imageFilePath $outPath
./crop 0 0 $middleH $middleW $imageFilePath $outPath

./split $imageFilePath $outPath

./rotate l $imageFilePath $outPath


echo $middle