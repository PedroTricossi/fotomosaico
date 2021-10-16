#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "utils.h"

void erroAlocacao(){
  fprintf(stderr, RED "Erro ao alocar memória \n");
  exit (1) ;
}

void erroArquivo(){
  fprintf(stderr, RED "Erro ao abrir arquivo \n");
  exit (1) ;
}

void formataCaminho(char* caminho){
    int last_c_index = strlen(caminho);
    if( caminho[last_c_index - 1] != '/' ){
        caminho[last_c_index] = '/';
        caminho[last_c_index + 1] = '\0';
    }
}

void** AlocaMatriz(int tamanho, long int largura, long int altura){
  void** m = NULL;

  m = malloc(altura * sizeof(void*));
  m[0] = malloc(altura * largura * tamanho);

  if (m == NULL || m[0] == NULL)
    erroAlocacao();
    
  for (int i=1; i < altura; i++)
      m[i] = m[0] + i * largura * tamanho;

  return m;
}

void freeTiles(t_image** tiles, int* num_tiles){
  int i;

  for(i=2; i < *num_tiles; i++){
    free(tiles[i]->cabecalho);
    free(tiles[i]->pixels[0]);
    free(tiles[i]->pixels);
    free(tiles[i]->corMedia);

    free(tiles[i]);
  }
  
  free(tiles);
  tiles = NULL;
}

void freeImage(t_image* image){
  free(image->cabecalho);
  free(image->pixels[0]);
  free(image->pixels);
  free(image->corMedia);

  free(image);
  image = NULL;
}
