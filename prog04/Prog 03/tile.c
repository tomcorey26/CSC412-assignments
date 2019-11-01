#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//
#include "../Image_IO/imageIO_TGA.h"

//--------------------------------------------------------------
//	Main function, expecting as arguments:
//		<images> outFolderPath
//	It returns an error code (0 for no error)
//--------------------------------------------------------------
int main(int argc, char *argv[])
{
    char *outFolderPath = argv[argc - 1];

    //array of images
    struct RasterImage images[argc - 1];

    // minus 1 to skip the last one
    int byteCount = 0;
    for (int i = 0; i < argc - 1; i++)
    {
        //	Read the image
        RasterImage image = readTGA(argv[i]);
        int totalImageBytes = image.bytesPerRow * image.numRows;
        byteCount += totalImageBytes;
        images[i] = image;
    }

    //allocate memory for final image
    // RasterImage img = newRasterImage(numRows, numCols, imgType);
}