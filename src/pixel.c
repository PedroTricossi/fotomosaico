#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "image.h"
#include "header.h"
#include "pixel.h"
#include "utils.h"

t_pixel** getPixel(FILE* file, t_header* h){
  t_pixel** pixel = (t_pixel**) allocateMatrixMemory(sizeof(t_pixel), h->width, h->height);

  fread(pixel[0], sizeof(t_pixel), h->width * h->height, file);

  return pixel;
}

void meanSquaredColor(t_header *header, t_pixel **pix, t_pixel *mean_color){
  int i, j;

  int num = 0;
  int r = 0;
  int g = 0;
  int b = 0;

  mean_color = malloc(sizeof(t_pixel));

  for(i=0; i < header->width; i++){
    for(j=0; j < header->height; j++){
      r += (pix[i][j].red) * (pix[i][j].red);

      g += (pix[i][j].green) * (pix[i][j].green);

      b += (pix[i][j].blue) * (pix[i][j].blue);

      num++;
    }
  }

  mean_color->red = sqrt(r / num);
  mean_color->green = sqrt(g / num);
  mean_color->blue = sqrt(b / num);

  printf(ANSI_COLOR_RED "Red: %d\n", mean_color->red,  ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_GREEN "Green: %d\n", mean_color->green, ANSI_COLOR_RESET "\n");
  printf(ANSI_COLOR_BLUE "Blue: %d\n", mean_color->blue, ANSI_COLOR_RESET "\n");
}

float meanRed(t_pixel *meanTile, t_pixel *imgImage){
  int r_mean = (imgImage->red + imgImage->red) / 2;

  int delta_r = (imgImage->red - imgImage->red);
  int delta_g = (imgImage->green - imgImage->green);
  int delta_b = (imgImage->blue - imgImage->blue);

  float delta_c = sqrt(
                    ((2 + r_mean/2) * (delta_r * delta_r)) + 
                    (4 * delta_g * delta_g) + 
                    ((2 + (255 - r_mean) / 256) * delta_b * delta_b ));
  
  
  return delta_c;
}