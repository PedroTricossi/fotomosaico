#ifndef __pixels__
#define __pixels__

#include "image.h"
#include "header.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} t_pixel;

t_pixel** getPixel(FILE* file, t_header* h);

void meanSquaredColor(t_header *header, t_pixel **pix, t_pixel *mean_color);

float meanRed(t_pixel *meanTile, t_pixel *imgImage);


#endif