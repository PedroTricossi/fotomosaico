#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include "image.h"
#include "utils.h"

#define TILESPATH "./tiles20/"
#define IMAGEPATH "photo5129875249075169750.ppm"
#define MAXWORDSIZE 1024

int main (int argc, char *argv[])
{
  FILE* input_file = stdin;
  FILE* output_file = stdout;
  t_image **tiles;
  t_image *image;
  int num_tales;
  int option;
  char* tiles_path;

  opterr = 0;
  tiles_path = malloc(sizeof(char) * MAXWORDSIZE);
  strcpy(tiles_path, TILESPATH);

  while ((option = getopt (argc, argv, "hp:i:o:")) != -1)
  switch (option)
    {
    case 'p':      
      strcpy(tiles_path, optarg);
      break;
    case 'i':
      input_file = fopen(optarg, "r");
      break;
    case 'o':
      output_file = fopen(optarg, "w+");
      if(output_file == NULL)
        fileError();
      break;
    case 'h':
      fprintf (stderr, "Usage: -i -o -p\n");
      exit (1) ;
      break;

    default:
      fprintf (stderr, "Sem informações mínimas necessárias, use -h para ajudar");
      exit (1) ;
    }

  tiles = readTiles(tiles_path, &num_tales);

  image = readImage(input_file);

  buildMosaic(image, tiles, &num_tales);

  saveImage(image, output_file);


  free(tiles_path);
  tiles_path = NULL;

  freeTiles(tiles, &num_tales);
  freeImage(image);
  fclose(input_file);
  fclose(output_file);
  
  return (0) ;
}