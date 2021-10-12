#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "header.h"
#include "pixel.h"
#include "utils.h"

t_pixel** getPixelP6(FILE* file, t_header* h){
  t_pixel** pixel = (t_pixel**) allocateMatrixMemory(sizeof(t_pixel), h->width, h->height);

  fread(pixel[0], sizeof(t_pixel), (h->height * h->width), file);

  return pixel;
}

t_pixel** getPixelP3(FILE* file, t_header* h){
  return NULL;
}

t_pixel *meanSquaredColor(t_header *header, t_pixel **pix){
  int i, j;
  int num = 1;
  unsigned int r = 0;
  unsigned int g = 0;
  unsigned int b = 0;
  t_pixel *mean_color = NULL;

  mean_color = malloc(sizeof(t_pixel));

  if(mean_color == NULL){
    perror ("Erro ao alocar memória") ;
    exit (1) ;
  }

  for(i=0; i < header->height; i++){
    for(j=0; j < header->width; j++){
      r += (pix[i][j].red) * (pix[i][j].red);

      g += (pix[i][j].green) * (pix[i][j].green);

      b += (pix[i][j].blue) * (pix[i][j].blue);

      num++;
    }
  }

  mean_color->red = sqrt(r / num);
  mean_color->green = sqrt(g / num);
  mean_color->blue = sqrt(b / num);

  return mean_color;
}

t_pixel* newPixel(int red, int green, int blue){
    t_pixel* p = malloc(sizeof(t_pixel));

    p->red = red;
    p->green = green;
    p->blue = blue;

    return p;
}

float meanRed(t_pixel *meanTile, t_pixel *imgImage){

  //printf("%d e %d \n", imgImage->red, meanTile->red);

  float r_mean = (imgImage->red + meanTile->red) / 2;

  float delta_r = (imgImage->red - meanTile->red);
  float delta_g = (imgImage->green - meanTile->green);
  float delta_b = (imgImage->blue - meanTile->blue);

  float delta_c = sqrt(
                    ((2 + r_mean/2) * (delta_r * delta_r)) + 
                    (4 * delta_g * delta_g) + 
                    ((2 + (255 - r_mean) / 256) * delta_b * delta_b ));
  
  return delta_c;
}