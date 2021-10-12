#ifndef __image__
#define __image__

#include "header.h"
#include "pixel.h"


typedef struct {
  t_header* head; 
  t_pixel* mean_color; 
  t_pixel** pixels;
} t_image;


t_image** readTiles(char* dirpath, int* numTales);

t_image* readImage(FILE* file);

void buildMosaic(t_image* main_img, t_image** tiles, int* tiles_n);

void saveImage(t_image *img, FILE* file);

#endif