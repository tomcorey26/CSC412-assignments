//====================================================================================
//	First attempt at simple image processing on the GPU, using OpenCL
//
//	This code is based on Apple's "Hello World" OpenCL code sample,
//	mixed with the "Lighthouse" library for loading/writing TGA image files
//
//	Authors:	Brett Saguid & Jean-Yves Hervé
//				©2015	3D Group for Interactive Visualization
//						Department of Computer Science and Statistics
//						University of Rhode Island
//====================================================================================

/*! \file main.c
	\brief Main file baybee

	The file given to base my code off of
	this is a doxy gen test ayeee
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//
#include "imageIO_TGA.h"
#include "RasterImage.h"
#include "helperFuncs.h"

#define OUT_PATH "../Output/makesure.tga"

int main(int argc, char **argv)
{
    //coordinates
    unsigned int x = atoi(argv[1]);
    unsigned int y = atoi(argv[2]);

    //crop values
    unsigned int croppedWidth = atoi(argv[3]);
    unsigned int croppedHeight = atoi(argv[4]);

    //input and output paths
    char *in = argv[5];
    //check if this ends with a /
    char *out = argv[6];

    //read in raster and store into struct
    RasterImage rasterObj = newImage(in);

    if (rasterObj.raster == NULL)
    {
        printf("Reading of image file failed.\n");
        exit(-1);
    }

    unsigned int imageSize = croppedWidth * croppedHeight;
    unsigned char *croppedRaster = (unsigned char *)malloc(imageSize * 4);
    unsigned char **croppedRaster2D = raster2D(croppedRaster, croppedHeight, croppedWidth);

    int rowStart = rasterObj.height - y - 1;
    int colStart = (x - 1) * 4;

    for (int i = croppedHeight - 1; i >= 0; i--)
    {
        colStart = (x - 1) * 4;
        for (int j = 0; j < croppedWidth * 4; j++)
        {
            croppedRaster2D[i][j] = rasterObj.raster2D[rowStart][colStart];
            colStart++;
        }
        rowStart--;
    }

    //	And we write back the modified image into the Output folder.
    if (writeTGA(OUT_PATH, croppedRaster, croppedHeight, croppedWidth))
    {
        printf("Writing out of the image failed.\n");
    }

    // Print a brief summary detailing the results
    //
    printf("Done!\n");

    return 0;
}
