#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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

  for (int i=1; i < height; i++)
      m[i] = m[0] + i * width * size;

  return m;
}

