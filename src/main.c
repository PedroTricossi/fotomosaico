#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>

#include "image.h"
#include "utils.h"


int main (int argc, char *argv[])
{
  FILE* arquivoEntrada = stdin;
  FILE* arquivoSaida = stdout;
  t_image **tiles;
  t_image *imagem;
  int num_tales;
  int option;
  char* diretorioTiles;

  opterr = 0;

  diretorioTiles = malloc(sizeof(char) * TAMANHOMAXIMO);
  
  // Se caminho para tiles não for passado como argumento, usa caminho padrão
  strcpy(diretorioTiles, CAMINHOTILES);

  while ((option = getopt (argc, argv, "hp:i:o:")) != -1)
  switch (option)
    {
    case 'p':      
      strcpy(diretorioTiles, optarg);
      break;
    case 'i':
      arquivoEntrada = fopen(optarg, "r");
      break;
    case 'o':
      arquivoSaida = fopen(optarg, "w+");
      if(arquivoSaida == NULL)
        erroArquivo();
      break;
    case 'h':
      fprintf (stderr, "Modo de uso:\n");
      fprintf (stderr, "-i: Caminho para imagem principal a ser usada\n");
      fprintf (stderr, "-o: Caminho para a imagem de saída (se não existir é criado)\n");
      fprintf (stderr, "-p: caminho para o diretório de tiles \n");
      exit (1) ;
      break;

    default:
      fprintf (stderr, "Sem informações mínimas necessárias, use -h para ajudar");
      exit (1) ;
    }

  //Le diretório de Tiles
  fprintf(stderr, GREEN "Iniciando Leitura das pastilhas \n");
  tiles = leTiles(diretorioTiles, &num_tales);

  //Le imagem principal
  fprintf(stderr, GREEN "Iniciando leitura da imagem principal\n");
  imagem = leImagem(arquivoEntrada);

  //Cria fotomosaico
  fprintf(stderr, GREEN "Iniciando Montagem do mosaico\n");
  criaMosaico(imagem, tiles, &num_tales);

  //Salva imagem criada
  fprintf(stderr, GREEN "Salvando imagem\n");
  salvaImagem(imagem, arquivoSaida);

  // Libera toda a memoria alocada
  fprintf(stderr, GREEN "Desalocando memória\n");
  free(diretorioTiles);
  diretorioTiles = NULL;

  freeTiles(tiles, &num_tales);
  freeImage(imagem);
  
  // Fecha arquicos de entrada e saida
  fclose(arquivoEntrada);
  fclose(arquivoSaida);
  
  return (0) ;
}