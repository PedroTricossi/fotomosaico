#ifndef __image__
#define __image__

#include "header.h"
#include "pixel.h"


typedef struct {
  t_header* head; 
  t_pixel* mean_color; 
  t_pixel** pixels;
} t_image;


t_image* readTiles();

void saveImage(t_image *img);

#endif