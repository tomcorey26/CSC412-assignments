
/*! \file dimensions.c
	\brief reports dimensions of image 

    flags: -h -w -v (height, width, verbose output)
    Flags can be combined
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
//
#include "./ImageIO/imageIO_TGA.h"
#include "helperFuncs.h"

#define IN_PATH "../Images/bottles.tga"
#define LOG_FILE_TYPE 'd'

//! check modifier type and print based off requested format
//! For when one modifier is passed
void printDimensionsSingleFlag(char *flag, unsigned int width, unsigned int height)
{
    if (strcmp(flag, "-h") == 0)
    {
        printf("%d \n", height);
    }
    else if (strcmp(flag, "-w") == 0)
    {
        printf("%d \n", width);
    }
    else if (strcmp(flag, "-v") == 0)
    {
        printf("Width: %d ", width);
        printf("Height: %d \n", height);
    }
    else
    {
        logCommand(LOG_FILE_TYPE, "Invalid Modifier passed \n");
        exit(-1);
    }
}
//! check modifier type and print based off requested format
//! For when two modifiers are passed
void printDimensionsDoubleFlag(char *flag1, char *flag2, unsigned int width, unsigned int height)
{
    if (strcmp(flag1, "-v") == 0 && strcmp(flag2, "-v") != 0)
    {
        if (strcmp(flag2, "-h") == 0)
        {
            printf("Height: %d \n", height);
        }
        else if (strcmp(flag2, "-w") == 0)
        {
            printf("Width: %d \n", width);
        }
        else
        {
            logCommand(LOG_FILE_TYPE, "Invalid Modifier passed \n");
            exit(-1);
        }
    }
    else if (strcmp(flag1, "-v") != 0 && strcmp(flag2, "-v") == 0)
    {
        if (strcmp(flag1, "-h") == 0)
        {
            printf("Height: %d \n", height);
        }
        else if (strcmp(flag1, "-w") == 0)
        {
            printf("Width: %d \n", width);
        }
        else
        {
            logCommand(LOG_FILE_TYPE, "Invalid Modifier passed \n");
            exit(-1);
        }
    }
    else
    {
        logCommand(LOG_FILE_TYPE, "Invalid Modifier passed \n");
        exit(-1);
    }
}

//! gets command args
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

    //initialize raster struct
    struct RasterImage raster;

    //error handling
    if (fileExists(argv[argc - 1]))
    {
        const char *path = argv[argc - 1];
        raster = newImage(path);
    }
    else
    {
        logCommand(LOG_FILE_TYPE, "Invalid path provided \n");
        exit(-1);
    }

    if (raster.raster == NULL)
    {
        logCommand(LOG_FILE_TYPE, "Reading of image file failed.\n");
        exit(-1);
    }

    //print dimensions based off arg count
    if (argc == 2)
    {
        printf("%d ", raster.width);
        printf("%d \n", raster.height);
    }
    else if (argc == 3)
    {
        char *flag = argv[1];
        printDimensionsSingleFlag(flag, raster.width, raster.height);
    }
    else if (argc == 4)
    {
        char *flag1 = argv[1];
        char *flag2 = argv[2];
        printDimensionsDoubleFlag(flag1, flag2, raster.width, raster.height);
    }
    else
    {
        logCommand(LOG_FILE_TYPE, "Incorrect amount of arguements passed.\n");
        exit(-1);
    }

    return 0;
}
