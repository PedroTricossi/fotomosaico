#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

void allocateError(){
  perror ("Erro ao Alocar memória");
  exit (1) ;
}

void fileError(){
  perror ("Erro ao abrir arquivo");
  exit (1) ;
}

void formatFilePath(char* path){
    int last_c_index = strlen(path);
    if( path[last_c_index - 1] != '/' ){
        path[last_c_index] = '/';
        path[last_c_index + 1] = '\0';
    }
}

void** allocateMatrixMemory(int size, long int width, long int height){
  void** m = NULL;

  m = malloc(height * sizeof(void*));
  m[0] = malloc(height * width * size);

  if (m == NULL || m[0] == NULL)
    allocateError();
    
  for (int i=1; i < height; i++)
      m[i] = m[0] + i * width * size;

  return m;
}

void freeTiles(t_image** tiles, int* num_tiles){
  int i;

  for(i=2; i < *num_tiles; i++){
    free(tiles[i]->head);
    free(tiles[i]->pixels[0]);
    free(tiles[i]->pixels);
    free(tiles[i]->mean_color);

    free(tiles[i]);
  }
  
  free(tiles);
  tiles = NULL;
}

void freeImage(t_image* image){
  free(image->head);
  free(image->pixels[0]);
  free(image->pixels);
  free(image->mean_color);

  free(image);
  image = NULL;
}
