#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

//
#include "./ImageIO/imageIO_TGA.h"
#include "./ImageIO/RasterImage.h"
#include "helperFuncs.h"

int main(int argc, char **argv)
{
    //log command
    for (int i = 0; i < argc + 1; ++i)
    {
        if (i == 1)
        {
            logArgs('s', argv[i]);
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
    //grab in and out paths
    char *in = argv[1];
    char *out = argv[2];

    RasterImage rasterObj = newImage(in);

    RasterImage red = newImage(in);
    RasterImage green = newImage(in);
    RasterImage blue = newImage(in);

    if (rasterObj.raster == NULL)
    {
        logCommand('s', "Reading of image file failed.\n");
        exit(-1);
    }

    for (unsigned int i = 0; i < rasterObj.height; i++)
    {
        for (unsigned int j = 0; j < rasterObj.width; j++)
        {

            //red
            red.raster2D[i][j * 4 + 1] = 0x00;
            red.raster2D[i][j * 4 + 2] = 0x00;
            //green
            green.raster2D[i][j * 4] = 0x00;
            green.raster2D[i][j * 4 + 2] = 0x00;
            //blue
            blue.raster2D[i][j * 4] = 0x00;
            blue.raster2D[i][j * 4 + 1] = 0x00;
        }
    }

    //get filename
    in = getFileName(in);

    //seperate name from tga and add cropped
    char redPath[50];
    char greenPath[50];
    char bluePath[50];
    strcpy(redPath, out);
    strcpy(greenPath, out);
    strcpy(bluePath, out);

    //get rid of everything passed the .
    char *name = strchr(in, '.');
    *name = '\0';

    //copy the file name
    char redInCopy[50];
    char greenInCopy[50];
    char blueInCopy[50];
    strcpy(redInCopy, in);
    strcpy(greenInCopy, in);
    strcpy(blueInCopy, in);

    //add appropriate endings
    strcat(redInCopy, "_r.tga");
    strcat(greenInCopy, "_g.tga");
    strcat(blueInCopy, "_b.tga");

    //add concatanate onto out path
    char redOutPath[50];
    char greenOutPath[50];
    char blueOutPath[50];
    strcpy(redOutPath, out);
    strcpy(greenOutPath, out);
    strcpy(blueOutPath, out);

    strcat(redOutPath, redInCopy);
    strcat(greenOutPath, greenInCopy);
    strcat(blueOutPath, blueInCopy);

    // And we write back the modified image into the Output folder.
    if (writeTGA(redOutPath, red.raster, rasterObj.height, rasterObj.width) || writeTGA(greenOutPath, green.raster, rasterObj.height, rasterObj.width) || writeTGA(blueOutPath, blue.raster, rasterObj.height, rasterObj.width))
    {
        logCommand('s', "Writing out of the image failed.\n");
    }

    // Print a brief summary detailing the results

    printf("Done!\n");

    return 0;
}
