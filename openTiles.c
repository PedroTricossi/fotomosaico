#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "openTiles.h"

#define ARQUIVO "tiles20/77EC56002E2501BFAAEE6DCD2EEAE55753C0A07C.ppm"
#define SAVE "teste.ppm"

t_header* getTileHeader(FILE* file){
  t_header *header = malloc(sizeof(t_header));

  fscanf(file, "%s", header->type);
  fscanf(file, "%d", &(header->width));
  fscanf(file, "%d", &(header->height));
  fscanf(file, "%d", &(header->max_value));

  printf("Tipo: %s\n", header->type);
  printf("Linha: %d\n", header->width);
  printf("Coluna: %d\n", header->height);
  printf("Max: %d\n", header->max_value);

  return header;
}

void** allocateMatrixMemory(int size, long int width, long int height){
  void** m;

  m = malloc(height * sizeof(void*));
  m[0] = malloc(height * width * size);
  for (int i=1; i < height; i++)
      m[i] = m[0] + i * width * size;

  return m;
}

t_pixel** getTilePixel(FILE* file, t_header* h){
  t_pixel** pixel = (t_pixel**) allocateMatrixMemory(sizeof(t_pixel), h->width, h->height);

  fread(pixel[0], sizeof(t_pixel), h->width * h->height, file);

  return pixel;
}

t_image* newImage(t_header* h, t_pixel** pxs){
    t_image* img = malloc(sizeof(t_image));

    img->head = h;
    img->pixels = pxs;

    return img;
}

t_image *readTiles(){
  
  FILE* arq;
  t_header *header = NULL;
  t_pixel **pixel = NULL;

  // abre o arquivo em modo leitura
  arq = fopen (ARQUIVO, "rb") ;

  if (!arq)
  {
    perror ("Erro ao abrir arquivo") ;
    exit (1) ;
  }

  header = getTileHeader(arq);
  pixel = getTilePixel(arq, header);

  // fecha o arquivo
  fclose (arq);

  return newImage(header, pixel);
}

void printPixel(t_pixel* p, FILE* file){
  fprintf(file, "%c%c%c", p->red, p->green, p->blue);
}

void saveImage(t_image *img){
  FILE* save;
  int i, j;

  save = fopen (SAVE, "w+") ;

  if (!save)
  {
    perror ("Erro ao abrir arquivo") ;
    exit (1) ;
  }

  fprintf(save, "%s\n%i %i\n%i\n", img->head->type, img->head->width, img->head->height, img->head->max_value);

  for(i=0;i < img->head->height; i++)
    for(j=0;j < img->head->width; j++)
      printPixel(&(img->pixels[i][j]), save);

  fclose(save);
}

void meanSquaredColor(t_image *img){
  int i, j;
  int num = 0;
  int r = 0;
  int g = 0;
  int b = 0;

  img->mean_color = malloc(sizeof(t_pixel));

  for(i=0; i < img->head->width; i++){
    for(j=0; j < img->head->height; j++){
      r += (img->pixels[i][j].red) * (img->pixels[i][j].red);

      g += (img->pixels[i][j].green) * (img->pixels[i][j].green);

      b += (img->pixels[i][j].blue) * (img->pixels[i][j].blue);

      num++;
    }
  }

  img->mean_color->red = sqrt(r / num);
  img->mean_color->green = sqrt(g / num);
  img->mean_color->blue = sqrt(b / num);

  printf("Red: %d\n", img->mean_color->red);
  printf("Green: %d\n", img->mean_color->green);
  printf("Blue: %d\n", img->mean_color->blue);
}


