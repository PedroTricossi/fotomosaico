#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

t_header *getTileHeader(FILE* file){
  int c;
  t_header *header = malloc(sizeof(t_header));

  if(header == NULL){
    perror ("Erro ao alocar memória") ;
    exit (1) ;
  }

  fscanf(file, "%s", header->type);
  fscanf(file, "%d", &(header->width));
  fscanf(file, "%d", &(header->height));
  fscanf(file, "%d", &(header->max_value));
  fscanf(file, "%d", &c);

  // printf("Tipo: %s\n", header->type);
  // printf("Linha: %d\n", header->width);
  // printf("Coluna: %d\n", header->height);
  // printf("Max: %d\n", header->max_value);

  return header;
}

int writeHeader(FILE* file, t_header *header){
  fprintf(file, "%s\n%d %d\n%d\n", header->type, header->width, header->height, header->max_value);

  return 1;   
}