//
// Created by Tom Corey on 11/1/19.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//
#include "./Image_IO/imageIO_TGA.h"
#include "./Image_IO/RasterImage.h"

//--------------------------------------------------------------
//	Main function, expecting as arguments:
//		<images> outFolderPath
//	It returns an error code (0 for no error)
//--------------------------------------------------------------
struct Grid
{
    int rows;
    int cols;
};

/**
 * Writes tile to specified row and coloum of tile grid
 * @param big raster of the big grid 
 * @param tile raster of the tile
 * @param row specified row for grid
 * @param col specified col for grid
 * 
**/
void writeTile(RasterImage *big, RasterImage *tile, int row, int col)
{
    int **b2D = (int **)big->raster2D;
    int **t2D = (int **)tile->raster2D;

    int ib;
    int jb;
    for (int it = 0, ib = row * tile->numRows; it < tile->numRows; it++, ib++)
    {
        for (int jt = 0, jb = col * tile->numCols; jt < tile->numCols; jt++, jb++)
        {
            b2D[ib][jb] = t2D[it][jt];
        }
    }
}

int main(int argc, char *argv[])
{
    char *outFolderPath = argv[argc - 1];

    //get width and height of sprite tile
    //square root closest to number of tiles
    int tileCount = argc - 2;
    double gNumRows = ceil(sqrt(tileCount));
    double gNumCols = ceil((float)tileCount / gNumRows);

    struct Grid spriteSheet = {gNumRows, gNumCols};
    RasterImage currTile = readTGA(argv[1]);
    RasterImage spriteGrid = newRasterImage(spriteSheet.rows * currTile.numRows, spriteSheet.cols * currTile.numCols, RGBA32_RASTER);

    int currTileIdx = 1;
    for (int i = spriteSheet.rows - 1; i >= 0; i--)
    {
        for (int j = 0; j < spriteSheet.cols; j++)
        {
            if (currTileIdx < argc - 1)
            {
                currTile = readTGA(argv[currTileIdx]);
                writeTile(&spriteGrid, &currTile, i, j);
                currTileIdx++;
                printf("%d\n", currTileIdx);
            }
        }
    }

    writeTGA(outFolderPath, &spriteGrid);
    deleteRasterImage(&currTile);
    deleteRasterImage(&spriteGrid);

    return 0;
}