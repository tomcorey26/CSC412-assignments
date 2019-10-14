#include <stdlib.h>
#include <stdio.h>

#include "imageIO_TGA.h"

#define LOG_PATH "log.txt"

//! Builder function that creates raster image struct
RasterImage newImage(int width, int height, ImageType type)
{
    struct RasterImage raster;

    raster.width = width;
    raster.height = height;
    raster.type = type;

    return raster;
}

// void freeImage(RasterImage* imagePtr) {

// }

void logCommand(char type, char *command)
{

    FILE *fp;

    fp = fopen(LOG_PATH, "a");

    if (type == 'd')
    {
        fprintf(fp, "%s", "dimensions ");
    }
    else if (type == 'c')
    {
        fprintf(fp, "%s", "crop ");
    }
    else if (type == 's')
    {
        fprintf(fp, "%s", "split ");
    }
    else if (type == 'r')
    {
        fprintf(fp, "%s", "rotate ");
    }
    else
    {
        fprintf(fp, "%s", "Unknown ");
    }

    fprintf(fp, "%s", command);

    fclose(fp);

    return;
}