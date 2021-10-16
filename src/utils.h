#ifndef __utils__
#define __utils__

#include "image.h"

#define RED "\e[0;31m"
#define NC "\e[0m"
#define GREEN "\033[0;32m"


#define CAMINHOTILES "./tiles20/"
#define TAMANHOMAXIMO 1024
#define ACONSTANTE 42

void erroAlocacao();

void erroArquivo();

void** AlocaMatriz(int size, long int width, long int height);

void formataCaminho(char* path);

void freeTiles(t_image** tiles, int* num_tiles);

void freeImage(t_image* image);

#endif