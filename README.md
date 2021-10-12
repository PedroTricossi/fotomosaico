# fotomosaico

O projeto fotomosaico é um trabalho avaliativo do curso de Ciência da computação da UFPR, e da disciplina de programação 2, ministrada pelo professor Lucas Ferrari no ano de 2021.

### Objetivo
Um fotomosaico ou mosaico fotográfico é uma fotografia construída a partir de imagens menores, ou “pastilhas” (do inglês tiles). As pastilhas são escolhidas de forma a reproduzir a cor e intensidade luminosa do bloco da imagem original correspondente.

### Modo de uso
*O projeto foi programada visando plataformas Linux, podendo não funcionar em ambientes Windows.*

1° Gerar o executavel:
`make`

2° Executar o programa:
`mosaico -i <imagem base para o mosaico> -o <nome do arquivo de saida> -p <diretório para os tiles>`

*OBS.: o programa aceita somente imagens .ppm*, para transformar qualquer imagem em PPM pode ser usado o imagemagick:

`mogrify -format ppm  -gravity center <nome da imagem>`

Para transforma novamente o resultado para o formato desejado basta:

`mogrify -format <formato> <nome de output>`