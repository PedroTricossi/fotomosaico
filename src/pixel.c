#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "image.h"
#include "header.h"
#include "pixel.h"
#include "utils.h"

t_pixel** pegaPixelP6(FILE* file, t_cabecalho* cabecalho){
  t_pixel** pixel = (t_pixel**) AlocaMatriz(sizeof(t_pixel), cabecalho->largura, cabecalho->altura);

  fread(pixel[0], sizeof(t_pixel), (cabecalho->altura * cabecalho->largura), file);

  return pixel;
}

t_pixel** pegaPixelP3(FILE* file, t_cabecalho* cabecalho){
  t_pixel** pixel = (t_pixel**) AlocaMatriz(sizeof(t_pixel), cabecalho->largura , cabecalho->altura);

    char* aux = NULL;
    char* tok = NULL;

    unsigned char* data = malloc(cabecalho->largura * cabecalho->altura * sizeof(t_pixel));

    int i = 0;
    while(fscanf(file, "%m[^\n]", &aux) != EOF){
        fgetc(file); 
        tok = strtok(aux, " ");
        while(tok != NULL){ 
            data[i] = (unsigned char) atoi(tok);
            i++;
            tok = strtok(NULL, " ");
        }
        free(aux);
    }
    aux = NULL;

    memcpy(pixel[0], data, cabecalho->largura * cabecalho->altura * sizeof(t_pixel));

    free(data);
    data = NULL;

    return pixel;
}

t_pixel *mediaCorQuadrada(t_cabecalho *cabecalho, t_pixel **pix){
  int i, j;
  int num = 1;
  float r = 0;
  float g = 0;
  float b = 0;
  t_pixel *mean_color = NULL;

  mean_color = malloc(sizeof(t_pixel));

  if(mean_color == NULL)
    erroAlocacao();

  for(i=0; i < cabecalho->altura; i++){
    for(j=0; j < cabecalho->largura; j++){
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

t_pixel* novoPixel(int red, int green, int blue){
    t_pixel* p = malloc(sizeof(t_pixel));

    if(p == NULL)
      erroAlocacao();

    p->red = red;
    p->green = green;
    p->blue = blue;

    return p;
}

float vermelhoMedio(t_pixel *mediaTile, t_pixel *mediaImagem){

  float r_medio = (mediaImagem->red + mediaTile->red) / 2;

  float delta_r = (mediaImagem->red - mediaTile->red);
  float delta_g = (mediaImagem->green - mediaTile->green);
  float delta_b = (mediaImagem->blue - mediaTile->blue);

  float delta_c = sqrt(
                    ((2 + r_medio/2) * (delta_r * delta_r)) + 
                    (4 * delta_g * delta_g) + 
                    ((2 + (255 - r_medio) / 256) * delta_b * delta_b ));
  
  return delta_c;
}