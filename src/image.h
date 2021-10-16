#ifndef __image__
#define __image__

#include "header.h"
#include "pixel.h"


typedef struct {
  t_cabecalho* cabecalho; 
  t_pixel* corMedia; 
  t_pixel** pixels;
} t_image;


t_image** leTiles(char* dirpath, int* numTales);

t_image* leImagem(FILE* file);

void criaMosaico(t_image* main_img, t_image** tiles, int* tiles_n);

void salvaImagem(t_image *img, FILE* file);

#endif