#ifndef __utils__
#define __utils__

#include "image.h"

void** allocateMatrixMemory(int size, long int width, long int height);

void formatFilePath(char* path);

void allocateError();

void fileError();

void freeTiles(t_image** tiles, int* num_tiles);

void freeImage(t_image* image);

#endif