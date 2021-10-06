#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "image.h"
#include "header.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ARQUIVO "tiles20/77EC56002E2501BFAAEE6DCD2EEAE55753C0A07C.ppm"
#define SAVE "teste.ppm"


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

  pixel = getPixel(arq, header);

  // fecha o arquivo
  fclose (arq);

  return newImage(header, pixel);
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

  writeHeader(save, img->head);

  fwrite(img->pixels[0], sizeof(t_pixel), (img->head->width * img->head->width), save);

  fclose(save);
}