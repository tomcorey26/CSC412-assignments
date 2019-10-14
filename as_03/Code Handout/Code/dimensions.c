
/*! \file dimensions.c
	\brief reports dimensions of image 

    flags: -h -w -v (height, width, verbose output)
    Flags can be combined
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
#include "helperFuncs.h"

#define IN_PATH "../Images/bottles.tga"
#define LOG_FILE_TYPE 'd'

//! gets command args
int main(int argc, char **argv)
{
    unsigned int numRows, numCols;
    ImageType imgType;
    unsigned char bytesPerPixel;

    unsigned char *raster = readTGA(IN_PATH, &numRows, &numCols, &imgType);
    unsigned char **raster_2D = raster2D(raster, numRows, numCols);

    printf("Width/Cols: %d", numCols);
    printf("Height/Rows: %d", numRows);
    // struct RasterImage rasterObj = newImage()

    if (raster == NULL)
    {
        printf("Reading of image file failed.\n");
        logCommand(LOG_FILE_TYPE, "Reading of image file failed.\n");
        exit(-1);
    }

    // Print a brief summary detailing the results
    //
    printf("Done!\n");

    return 0;
}
