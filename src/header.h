#ifndef __header__
#define __header__
#include <stdio.h>


typedef struct{
  char type[3]; 
  int width;
  int height; 
  int max_value; 
} t_header;

t_header *getTileHeader(FILE* file);

int writeHeader(FILE* file, t_header *header);

#endif