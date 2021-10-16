#ifndef __header__
#define __header__
#include <stdio.h>


typedef struct{
  char tipo[3]; 
  int largura;
  int altura; 
  int valor_max; 
} t_cabecalho;

t_cabecalho *Pegacabecalho(FILE* file);

void escreveCabecalho(FILE* file, t_cabecalho *cabecalho);

#endif