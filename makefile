CFLAGS = -Wall -std=c99 -g  # gerar "warnings" detalhados e infos de depuração	
LDLIBS = -lm 
CC = gcc
 
objs = src/main.o src/image.o src/header.o src/pixel.o src/utils.o

# regra default (primeira regra)
all: mosaico
	$(CC) $(CFLAGS) -o mosaico $(objs) $(LDLIBS)
 
# regras de ligacao
mosaico: $(objs)
 
# regras de compilação
main.o: main.c image.h 
image.o: image.c image.h
header.o: header.c header.h
pixel.o: pixel.c pixel.h
utils.o: utils.c utils.h
 
# remove arquivos temporários
clean:
	-rm -f $(objs) *~
 
# remove tudo o que não for o código-fonte
purge: clean
	-rm -f mosaico