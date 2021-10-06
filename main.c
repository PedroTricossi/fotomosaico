#include <stdio.h>
#include <stdlib.h>
#include "openTiles.h" 
 
int main (int argc, char *argv[])
{
  t_image *image;

  image = readTiles();

  meanSquaredColor(image);
  
  saveImage(image);
  
  return (0) ;
}