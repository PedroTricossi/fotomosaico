#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
#include <string.h>
#include "utils.h"
#include "image.h"
#include "header.h"

// Cria a estrutura de Imagem com o cabeçalho e os pixel lido
t_image* criaImagem(t_cabecalho* cabecalho, t_pixel** pixel){
    t_image* img = malloc(sizeof(t_image));

    if(img == NULL)
      erroAlocacao();

    img->cabecalho = cabecalho;
    img->pixels = pixel;
    img->corMedia = mediaCorQuadrada(cabecalho, pixel);

    return img;
}

// Pega as informações de um Tile (cabeçalho e pixels)
t_image *pegaTiles(char* tile){
  FILE* file;
  t_cabecalho *cabecalho = NULL;
  t_pixel **pixel = NULL;

  file = fopen (tile, "r") ;

  if (!file)
    erroArquivo();

  cabecalho = Pegacabecalho(file);

  if (!(strcmp(cabecalho->tipo, "P6")))
    pixel = pegaPixelP6(file, cabecalho);

  if (!(strcmp(cabecalho->tipo, "P3")))
    pixel = pegaPixelP3(file, cabecalho);

  fclose (file);

  return criaImagem(cabecalho, pixel);
}

// Le todos os Tiles do diretório indicado pela main
t_image** leTiles(char* diretorio, int* numTales){
  char *caminhoTiles;
  struct dirent** dirent;
  t_image** tiles;

  *numTales = scandir(diretorio, &dirent, NULL, alphasort);

  *numTales = *numTales - 2;

  if (*numTales < 0)
    erroArquivo();
  
  tiles = malloc((*numTales) * sizeof(t_image));
  caminhoTiles = malloc(TAMANHOMAXIMO * sizeof(char));

  if( tiles == NULL || caminhoTiles == NULL)
    erroAlocacao();

  for(int i = 2; i < (*numTales); i++){
    strcpy(caminhoTiles, diretorio);

    formataCaminho(caminhoTiles);
    
    strcat(caminhoTiles, dirent[i]->d_name);

    tiles[i] = pegaTiles(caminhoTiles);

    free(dirent[i]);
  }

  fprintf(stderr, GREEN "Foram lidos %d tiles\n", *numTales);
  fprintf(stderr, GREEN "Os tiles são do tamanhos %dX%d\n", tiles[42]->cabecalho->altura, tiles[42]->cabecalho->largura);

  
  free(dirent);
  free(caminhoTiles);
  caminhoTiles = NULL;

  return tiles;
}

// Le imagem principal
t_image* leImagem(FILE* file){
  t_cabecalho *cabecalho = NULL;
  t_pixel **pixel = NULL;

  cabecalho = Pegacabecalho(file);

  if (!(strcmp(cabecalho->tipo, "P6")))
    pixel = pegaPixelP6(file, cabecalho);

  if (!(strcmp(cabecalho->tipo, "P3")))
    pixel = pegaPixelP3(file, cabecalho);
  
  fprintf(stderr, GREEN "O tamanho da imagem principal é do tipo %s e de tamanho %dX%d\n", cabecalho->tipo, cabecalho->altura, cabecalho->largura);

  return criaImagem(cabecalho, pixel);
}

// Corta um pedaço da imagem principal do tamanho do TILE
// NOTA PARA DEFESA -> Inspirado em como uma CNN trabalha para ler imagem
// NOTA PARA DEFESA -> Se o Tile da borda for maior que a imagem, completa com pixels brancos para afetar da menor forma
// possivel o calculo da distância
t_image* cortaImagem(t_image* main_img, int lin, int col, int largura, int altura){
    t_pixel** recorte = (t_pixel**) AlocaMatriz(sizeof(t_pixel), largura, altura);
    t_pixel* novoPix = NULL;

    for(int i = 0; i < altura; i++)
      for(int j = 0; j < largura; j++){
          if( (lin + i < main_img->cabecalho->altura) && (col + j < main_img->cabecalho->largura) )
              recorte[i][j] = main_img->pixels[i + lin][j + col];
          else {
              novoPix = novoPixel(255, 255, 255);
              recorte[i][j] = *novoPix;
              free(novoPix);
              novoPix = NULL;
          }
      }

    t_cabecalho* cabecalho = malloc(sizeof(t_cabecalho));

    if (cabecalho == NULL)
      erroAlocacao();

    cabecalho->largura = largura;
    cabecalho->altura = altura;

    return criaImagem(cabecalho, recorte);
}

// Compara o trecho recortado com todos os tiles e pega aquele com a menor distancia (base de medida: red mean)
t_image* pegaSimilar(t_pixel* main_color, t_image** tiles, int* tiles_n){
    int pos = 42;
    int i;
    float current_c = 0;
    
    float closest_c = vermelhoMedio(main_color, tiles[pos]->corMedia); 
    
    for(i = 0; i < (*tiles_n); i++){
        current_c = vermelhoMedio(main_color, tiles[i]->corMedia);
        if(closest_c > current_c){
            closest_c = current_c;
            pos = i;
        }
    }

    return tiles[pos];
}

// Troca a região recortada da imagem pelo Tile mais proximo
void trocaPorTile(t_image* main_img, int lin, int col, t_image* tile){
  int k, p;
  for(k = 0; k < tile->cabecalho->altura; k++){
    for(p = 0; p < tile->cabecalho->largura; p++){
       if( (lin + k < main_img->cabecalho->altura) && (col + p < main_img->cabecalho->largura) )
        main_img->pixels[lin + k][col + p] = tile->pixels[k][p];
    }
  }
            
}

// Cria o fotomosaico urilizando 3 passos principais
// 1 - Recorta uma parte da imagem na mesma medida dos Tiles
// 2 - Pega o Tile mais similar a região recortada
// 3 - subtitui a região pelo Tile
void criaMosaico(t_image* main_img, t_image** tiles, int* tiles_n){
    int tile_altura = tiles[42]->cabecalho->altura;
    int tile_largura = tiles[42]->cabecalho->largura;

    int i, j;
    
    t_image* tile = NULL;
    t_image* croppedImg = NULL;
    
    
    for(i = 0; i < main_img->cabecalho->altura; i+= tile_altura){
      for(j = 0; j < main_img->cabecalho->largura; j+= tile_largura){
        croppedImg = cortaImagem(main_img, i, j, tile_largura, tile_altura);
        tile = pegaSimilar(croppedImg->corMedia, tiles, tiles_n);
        trocaPorTile(main_img, i, j, tile);
        freeImage(croppedImg);
        croppedImg = NULL;
      }
    }

    croppedImg = NULL;
    tile = NULL;
}

// Salva o fotomosaico 
void salvaImagem(t_image *img, FILE* file){
  int i, j;

  escreveCabecalho(file, img->cabecalho);
  fprintf(file, "0 \n");

  if (!(strcmp(img->cabecalho->tipo, "P6")))
    fwrite(img->pixels[0], sizeof(t_pixel), (img->cabecalho->altura * img->cabecalho->largura), file);


  if (!(strcmp(img->cabecalho->tipo, "P3"))){
    for(i=0; i < img->cabecalho->altura;i++){
      for(j=0; j < img->cabecalho->largura; j++){
        fprintf(file, "%d %d %d\n", img->pixels[i][j].red, img->pixels[i][j].green, img->pixels[i][j].blue);
      }
    }
  }
}