#ifndef IMAGE_IO_TGA_H
#define IMAGE_IO_TGA_H

#include "RasterImage.h"

unsigned char *readTGA(const char *fileName, unsigned int *nbCols, unsigned int *nbRows, ImageType *theType);
int writeTGA(char *fileName, unsigned char *theData, unsigned int nbRows, unsigned int nbCols);
unsigned char **raster2D(unsigned char *s, unsigned int numRows, unsigned int numCols);
#endif //	IMAGE_IO_TGA_H
