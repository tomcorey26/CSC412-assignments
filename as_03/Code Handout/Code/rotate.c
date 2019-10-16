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

int main(int argc, char **argv)
{
    //log command
    for (int i = 0; i < argc + 1; ++i)
    {
        if (i == 1)
        {
            logArgs('r', argv[i]);
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

    enum rotationType
    {
        left,
        right,
        dub
    };

    enum rotationType rotation;
    //find out type of rotation
    if (strlen(argv[1]) == 2)
    {
        rotation = dub;
    }
    else
    {
        char r = *(argv[1]);
        if (r == 'l')
        {
            rotation = left;
        }
        else
        {
            rotation = right;
        }
    }

    char *in = argv[2];
    char *out = argv[3];

    RasterImage rasterObj = newImage(in);

    if (rasterObj.raster == NULL)
    {
        logCommand('s', "Reading of image file failed.\n");
        exit(-1);
    }

    //allocate memory for rotated image
    unsigned int bytesPerRow = 4 * rasterObj.width;
    unsigned int imageSize = rasterObj.width * rasterObj.height;
    unsigned char *rotatedRaster = (unsigned char *)malloc(imageSize * 4);

    //set 2d array pointers based off of requested rotation
    unsigned char **rotatedRaster2D;
    if (rotation == dub)
    {
        //for double rotation
        rotatedRaster2D = raster2D(rotatedRaster, rasterObj.height, rasterObj.width);
    }
    else
    {
        rotatedRaster2D = raster2D(rotatedRaster, rasterObj.width, rasterObj.height);
    }

    for (unsigned int i = 0; i < rasterObj.height; i++)
    {
        for (unsigned int j = 0; j < rasterObj.width; j++)
        {
            //manipulate pixels based of rotaion
            if (rotation == right)
            {
                //rotateright
                rotatedRaster2D[rasterObj.width - j - 1][i * 4] = rasterObj.raster2D[i][j * 4];
                rotatedRaster2D[rasterObj.width - j - 1][i * 4 + 1] = rasterObj.raster2D[i][j * 4 + 1];
                rotatedRaster2D[rasterObj.width - j - 1][i * 4 + 2] = rasterObj.raster2D[i][j * 4 + 2];
                rotatedRaster2D[rasterObj.width - j - 1][i * 4 + 3] = rasterObj.raster2D[i][j * 4 + 3];
            }
            else if (rotation == left)
            {
                //rotate left
                rotatedRaster2D[j][(rasterObj.height - i - 1) * 4] = rasterObj.raster2D[i][j * 4];
                rotatedRaster2D[j][(rasterObj.height - i - 1) * 4 + 1] = rasterObj.raster2D[i][j * 4 + 1];
                rotatedRaster2D[j][(rasterObj.height - i - 1) * 4 + 2] = rasterObj.raster2D[i][j * 4 + 2];
                rotatedRaster2D[j][(rasterObj.height - i - 1) * 4 + 3] = rasterObj.raster2D[i][j * 4 + 3];
            }
            else
            {
                //rotate twice
                rotatedRaster2D[rasterObj.height - i - 1][(rasterObj.width - j - 1) * 4] = rasterObj.raster2D[i][j * 4];
                rotatedRaster2D[rasterObj.height - i - 1][(rasterObj.width - j - 1) * 4 + 1] = rasterObj.raster2D[i][j * 4 + 1];
                rotatedRaster2D[rasterObj.height - i - 1][(rasterObj.width - j - 1) * 4 + 2] = rasterObj.raster2D[i][j * 4 + 2];
                rotatedRaster2D[rasterObj.height - i - 1][(rasterObj.width - j - 1) * 4 + 3] = rasterObj.raster2D[i][j * 4 + 3];
            }
        }
    }

    //get filename
    in = getFileName(in);

    //make a path copy
    char path[50];
    strcpy(path, out);

    //get rid of everything passed the .
    char *name = strchr(in, '.');
    *name = '\0';

    //copy the file name
    char inCopy[50];
    strcpy(inCopy, in);

    //add appropriate endings
    strcat(inCopy, " [cropped].tga");

    //add concatanate onto out path
    char outPath[50];
    strcpy(outPath, out);
    strcat(outPath, inCopy);
    printf("%s", outPath);

    // And we write back the modified image into the Output folder.
    if (rotation == dub)
    {
        //flipped twice means height and width stay the same
        if (writeTGA(outPath, rotatedRaster, rasterObj.height, rasterObj.width))
        {
            logCommand('s', "Writing out of the image failed.\n");
        }
    }
    else
    {
        //flipped once requires swapped height and width
        if (writeTGA(outPath, rotatedRaster, rasterObj.width, rasterObj.height))
        {
            logCommand('s', "Writing out of the image failed.\n");
        }
    }

    printf("Done!\n");

    return 0;
}
