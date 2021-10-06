#ifndef __openTiles__
#define __openTiles__

typedef struct{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
} t_pixel;

typedef struct{
  char type[3]; // O tipo da imagem  
  int width; // A largura da imagem
  int height; // A altura da imagem
  int max_value; // O valor máximo dos pixeis da imagem
} t_header;

typedef struct {
  t_header* head; // O cabeçalho do arquivo
  t_pixel* mean_color; // Cor predominante da imagem
  t_pixel** pixels; // Uma matriz utilizada para armazenar os pixeis
} t_image;


t_image* readTiles();

void saveImage(t_image *img);

void meanSquaredColor(t_image *img);

#endif