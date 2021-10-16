#ifndef __pixels__
#define __pixels__

#include "header.h"

typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} t_pixel;

t_pixel** pegaPixelP6(FILE* file, t_cabecalho* h);
t_pixel** pegaPixelP3(FILE* file, t_cabecalho* h);

t_pixel *mediaCorQuadrada(t_cabecalho *cabecalho, t_pixel **pix);

float vermelhoMedio(t_pixel *meanTile, t_pixel *imgImage);

t_pixel* novoPixel(int red, int green, int blue);


#endif