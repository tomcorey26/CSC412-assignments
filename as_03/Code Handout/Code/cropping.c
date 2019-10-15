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
#include <string.h>
//
#include "imageIO_TGA.h"
#include "RasterImage.h"
#include "helperFuncs.h"

#define OUT_PATH "../Output/makesure.tga"
#define LOG_FILE_TYPE 'c'

int main(int argc, char **argv)
{

    //log command
    for (int i = 0; i < argc + 1; ++i)
    {
        if (i == 1)
        {
            logArgs(LOG_FILE_TYPE, argv[i]);
        }
        else if (i == argc)
        {
            logArgs('n', "\n");
        }
        else
        {
            logArgs('n', argv[i]);
        }
    }

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

    //allocate memory for the cropped raster
    unsigned int imageSize = croppedWidth * croppedHeight;
    unsigned char *croppedRaster = (unsigned char *)malloc(imageSize * 4);
    unsigned char **croppedRaster2D = raster2D(croppedRaster, croppedHeight, croppedWidth);

    //set markers for starting points of raster
    int rowStart = rasterObj.height - y - 1;
    int colStart = (x - 1) * 4;

    //loop through crop raster and add specified pixels
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

    // get the input file name
    strtok(in, "/");

    while (in != NULL)
    {
        in = strtok(NULL, "/");
        if (strstr(in, ".tga"))
        {
            break;
        }
    }

    //seperate name from tga and add cropped
    char outName[50];
    strcpy(outName, out);
    char *name = strchr(in, '.');
    *name = '\0';
    in = strcat(in, " [cropped].tga");

    //append to out string
    out = strcat(outName, in);

    //	And we write back the modified image into the Output folder.
    if (writeTGA(outName, croppedRaster, croppedHeight, croppedWidth))
    {
        printf("Writing out of the image failed.\n");
    }

    // Print a brief summary detailing the results
    //
    printf("Done!\n");

    return 0;
}
