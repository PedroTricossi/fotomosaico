#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include "utils.h"
#include "image.h"
#include "header.h"

t_image* newImage(t_header* h, t_pixel** pxs){
    t_image* img = malloc(sizeof(t_image));

    img->head = h;
    img->pixels = pxs;

    img->mean_color = meanSquaredColor(h, pxs);

    return img;
}

t_image *getTiles(char* tile){
  FILE* file;
  t_header *header = NULL;
  t_pixel **pixel = NULL;

  file = fopen (tile, "r") ;

  if (!file)
  {
    perror ("Erro ao abrir arquivo") ;
    exit (1) ;
  }

  header = getTileHeader(file);

  pixel = getPixelP6(file, header);

  fclose (file);

  return newImage(header, pixel);
}

t_image** readTiles(char* dirpath, int* numTales){
  char *filepath;
  struct dirent** dirent;
  t_image** tiles;

  *numTales = scandir(dirpath, &dirent, NULL, alphasort);

  if (*numTales < 0)
      perror("scandir");
  
  tiles = malloc((*numTales) * sizeof(t_image));

  filepath = malloc(1064 * sizeof(char));

  for(int i = 2; i < (*numTales); i++){
    strcpy(filepath, dirpath);

    formatFilePath(filepath);
    
    strcat(filepath, dirent[i]->d_name);

    tiles[i] = getTiles(filepath);

    free(dirent[i]);
  }
  
  free(dirent);
  free(filepath);
  filepath = NULL;

  return tiles;
}

t_image* readImage(FILE* file){
  t_header *header = NULL;
  t_pixel **pixel = NULL;

  header = getTileHeader(file);

  if (!(strcmp(header->type, "P6")))
    pixel = getPixelP6(file, header);

  if (!(strcmp(header->type, "P3")))
    pixel = getPixelP3(file, header);

  return newImage(header, pixel);
}

t_image* cropImg(t_image* main_img, int lin, int col, int width, int height){
    t_pixel** cropPixel = (t_pixel**) allocateMatrixMemory(sizeof(t_pixel), width, height);
    t_pixel* newPx = NULL;

    for(int i = 0; i < height; i++)
      for(int j = 0; j < width; j++){
          if( (lin + i < main_img->head->height) && (col + j < main_img->head->width) )
              cropPixel[i][j] = main_img->pixels[i + lin][j + col];
          else {
              newPx = newPixel(255, 255, 255);
              cropPixel[i][j] = *newPx;
              free(newPx);
              newPx = NULL;
          }
      }

    t_header* h = malloc(sizeof(t_header));

    h->width = width;
    h->height = height;

    return newImage(h, cropPixel);
}

t_image* similarTile(t_pixel* main_color, t_image** tiles, int* tiles_n){
    int pos = 42;
    int i;
    float current_c = 0;
    
    float closest_c = meanRed(main_color, tiles[pos]->mean_color); 
    
    for(i = 2; i < (*tiles_n); i++){
        current_c = meanRed(main_color, tiles[i]->mean_color);
        if(closest_c > current_c){
            closest_c = current_c;
            pos = i;
        }
    }

    return tiles[pos];
}

void replaceTile(t_image* main_img, int lin, int col, t_image* tile){
  int k, p;
  for(k = 0; k < tile->head->height; k++){
    for(p = 0; p < tile->head->width; p++){
       if( (lin + k < main_img->head->height) && (col + p < main_img->head->width) )
        main_img->pixels[lin + k][col + p] = tile->pixels[k][p];
    }
  }
            
}

void buildMosaic(t_image* main_img, t_image** tiles, int* tiles_n){
    if(*tiles_n < 1){
        fprintf(stderr, "No tiles were found to be used in the mosaic.\n");
        exit(1);
    }

    int tile_height = tiles[42]->head->height;
    int tile_width = tiles[42]->head->width;

    int i, j;
    
    t_image* tile = NULL;
    t_image* croppedImg = NULL;
    
    
    for(i = 2; i < main_img->head->height; i+= tile_height){
      for(j = 2; j < main_img->head->width; j+= tile_width){
        croppedImg = cropImg(main_img, i, j, tile_width, tile_height);
        tile = similarTile(croppedImg->mean_color, tiles, tiles_n);
        replaceTile(main_img, i, j, tile);
        freeImage(croppedImg);
        croppedImg = NULL;
      }
    }

    croppedImg = NULL;
    tile = NULL;
}



void saveImage(t_image *img, FILE* file){

  writeHeader(file, img->head);
  
  fwrite(img->pixels[0], sizeof(t_pixel), (img->head->height * img->head->width), file);
}