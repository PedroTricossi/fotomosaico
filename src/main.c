#include <stdio.h>
#include <stdlib.h>

#include "image.h" 
 
int main (int argc, char *argv[])
{
  t_image *image;

  image = readTiles();
  
  saveImage(image);
  
  return (0) ;
}