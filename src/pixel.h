#ifndef __pixels__
#define __pixels__

#include "header.h"

typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} t_pixel;

t_pixel** getPixelP6(FILE* file, t_header* h);
t_pixel** getPixelP3(FILE* file, t_header* h);

t_pixel *meanSquaredColor(t_header *header, t_pixel **pix);

float meanRed(t_pixel *meanTile, t_pixel *imgImage);

t_pixel* newPixel(int red, int green, int blue);


#endif