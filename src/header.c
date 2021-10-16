#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "utils.h"

// Pega as informações contidas no cabeçalho da imagem baseado na descrição oficial
// NOTA PARA DEFESA -> necessário pular um bit entre o cabeçalho e a matriz de pixel
t_cabecalho *Pegacabecalho(FILE* file){
  int c;
  t_cabecalho *cabecalho = malloc(sizeof(t_cabecalho));

  if(cabecalho == NULL)
    erroAlocacao();

  fscanf(file, "%s", cabecalho->tipo);
  fscanf(file, "%d", &(cabecalho->largura));
  fscanf(file, "%d", &(cabecalho->altura));
  fscanf(file, "%d", &(cabecalho->valor_max));
  fscanf(file, "%d", &c);

  return cabecalho;
}

// Escreve o cabeçalho no arquivo
void escreveCabecalho(FILE* file, t_cabecalho *cabecalho){
  fprintf(file, "%s\n%d %d\n%d\n", cabecalho->tipo, cabecalho->largura, cabecalho->altura, cabecalho->valor_max);
}