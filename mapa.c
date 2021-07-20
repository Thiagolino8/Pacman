#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

int i,j;

void lemapa(FASE* m){
	FILE* f;
	f = fopen("mapa.txt", "r");
	if(f == 0){
		printf("Erro na leitura do mapa\n");
		exit(1);
	}
	
	fscanf(f, "%d %d", &(m->linhas), &(m->colunas));
	
	alocamapa(m);
	
	for(int i = 0; i < 5; i++){
		fscanf(f, "%s", m->mapa[i]);
	}
	fclose(f);
}

 void alocamapa(FASE* m){
	 m->mapa = malloc(sizeof(char*) * m->linhas);
	for(int i = 0; i < m->linhas; i++){
		(m->mapa[i] = malloc(sizeof(char) * (m->colunas + 1)));
	}
 }

int encontramapa(FASE* m, POSICAO* h, char c){
	for(int i = 0; i < m->linhas; i++){
		for(int j = 0; j < m->colunas; j++){
			if(m->mapa[i][j] == c){
				h->x = i;
				h->y = j;
				return 1;
			}
		}
	}
	return 0;
}

int ehvalida(FASE* m, int x, int y){
	if(x >= m->linhas){
		return 0;
	}
	if(y >= m->colunas){
		return 0;
	}
	return 1;
}

void andanomapa(FASE* m, int xorigem, int yorigem, int xdestino, int ydestino){
	char personagem = m->mapa[xorigem][yorigem];
	m->mapa[xdestino][ydestino] = personagem;
	m->mapa[xorigem][yorigem] = VAZIO;
}

void copiamapa(FASE* destino, FASE* origem){
	destino->linhas = origem->linhas;
	destino->colunas = origem->colunas;
	alocamapa(destino);
	for(int i = 0; i < origem->linhas; i++){
		strcpy(destino->mapa[i], origem->mapa[i]);
	}
}

int podeandar(FASE* m, char personagem, int x, int y){
	return 
		ehvalida(m, x, y) && 
		!ehparede(m, x, y) &&
		!ehpersonagem(m, personagem, x, y);
}

void liberamapa(FASE* m){
	for(int i = 0; i < m->linhas; i++){
		free(m->mapa[i]);
	}
	free(m->mapa);
}

int ehparede(FASE* m, int x, int y){
    return 
        m->mapa[x][y] == PAREDE_LATERAL ||
        m->mapa[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(FASE* m, char personagem, int x, int y){
    return
        m->mapa[x][y] == personagem;
}