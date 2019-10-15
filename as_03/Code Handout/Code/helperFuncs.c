#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imageIO_TGA.h"

#define LOG_PATH "log.txt"

//! Builder function that creates raster image struct
RasterImage newImage(const char *filename)
{
    struct RasterImage rasterObj;

    unsigned int numRows, numCols;
    ImageType imgType;

    rasterObj.raster = readTGA(filename, &numRows, &numCols, &imgType);
    rasterObj.raster2D = raster2D(rasterObj.raster, numRows, numCols);
    rasterObj.width = numCols;
    rasterObj.height = numRows;
    rasterObj.type = imgType;

    return rasterObj;
}

// void freeImage(RasterImage* imagePtr) {

// }

int fileExists(const char *file)
{
    FILE *fs = fopen(file, "r");

    if (fs == NULL)
    {
        return 0;
    }

    fclose(fs);

    return 1;
}
//! Logs commandline args
void logArgs(char type, char *command)
{

    FILE *fp;

    fp = fopen(LOG_PATH, "a");

    fprintf(fp, "%s ", command);

    fclose(fp);

    return;
}

//! Logs commands and errors from programs
void logCommand(char type, char *command)
{
    printf("%s", command);

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

    fprintf(fp, "%s", command);

    fclose(fp);

    return;
}

char *getFileName(char *in)
{
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
    return in;
}