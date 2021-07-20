#ifndef _MAPA_H_
#define _MAPA_H_

#define VAZIO '.'
#define HEROI '@'
#define FANTASMA 'F'
#define PILULA 'P'
#define PAREDE_LATERAL '|'
#define PAREDE_HORIZONTAL '-'

struct fase{
	char** mapa;
	int linhas, colunas;
};
typedef struct fase FASE;

struct posicao{
	int x, y;
};
typedef struct posicao POSICAO;

int encontramapa(FASE* m, POSICAO* h, char c);
void liberamapa(FASE* m);
void lemapa(FASE* m);
void alocamapa(FASE* m);
int ehvalida(FASE* m, int x, int y);
void andanomapa(FASE* m, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(FASE* destino, FASE* origem);
int podeandar(FASE* m, char personagem, int x, int y);
int ehparede(FASE* m, int x, int y);
int ehpersonagem(FASE* m, char personagem, int x, int y);

#endif