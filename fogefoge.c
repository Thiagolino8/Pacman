#include <stdio.h>
#include <stdlib.h>
#include <TIME.h>
#include <windows.h>
#include "fogefoge.h"
#include "mapa.h"
#include "ui.h"

FASE m;
POSICAO h;
int i, j;
int tempilula = 0;
int morreu = 0;

void move(char direcao){
	
	int proximox = h.x;
	int proximoy = h.y;

	switch(direcao){
		case ESQUERDA:
			proximoy--;
			break;
		case CIMA:
			proximox--;
			break;
		case BAIXO:
			proximox++;
			break;
		case DIREITA:
			proximoy++;
			break;
	}
	if(!podeandar(&m, HEROI, proximox, proximoy)) {
		return;
	}
	if(ehpersonagem(&m, PILULA, proximox, proximoy)){
		tempilula = 1;
	}
	andanomapa(&m, h.x, h.y, proximox, proximoy);
	h.x = proximox;
	h.y = proximoy;
}

int ehdirecao(char direcao){
	return direcao == 'a' || direcao == 'w' || direcao == 's' || direcao == 'd';
}

void fantasma(){
	FASE copia;
	copiamapa(&copia, &m);
	for(int i = 0; i < copia.linhas; i++){
		for(int j = 0; j < copia.colunas; j++){
			if(copia.mapa[i][j] == FANTASMA){
				int xdestino, ydestino;
				int encontrou = ondeofantasmavai(i, j, &xdestino, &ydestino);
				if(encontrou){
					andanomapa(&m, i, j, xdestino, ydestino);
				}
			}
		}
	}
	liberamapa(&copia);
}

int ondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino){
	int opcoes[4][2] ={	{xatual, yatual + 1}, {xatual + 1, yatual}, {xatual, yatual - 1}, {xatual - 1, yatual}};
	
	srand(time(0));
	for(int i = 0; i < 10; i++){
		int posicao = rand()%4;
		if(podeandar(&m, FANTASMA ,opcoes[posicao][0], opcoes[posicao][1])) {
			*xdestino = opcoes[posicao][0];
			*ydestino = opcoes[posicao][1];
			return 1;
		}
	}
	return 0;
}

int acabou(){
	POSICAO pos;

	int perdeu = !encontramapa(&m, &pos, HEROI);
	int ganhou = !encontramapa(&m, &pos, FANTASMA);

	return ganhou || perdeu;
}


void explodepilula(){
	if(!tempilula){
		return;
	}
    explodepilula2(h.x, h.y, 0, 1, 3);
    explodepilula2(h.x, h.y, 0, -1, 3);
    explodepilula2(h.x, h.y, 1, 0, 3);
    explodepilula2(h.x, h.y, -1, 0, 3);

	tempilula = 0;

	printf("Explodiu\n");
}
	
void explodepilula2(int x, int y, int somax, int somay, int qtd){

    if(qtd == 0) return;

    int novox = x+somax;
    int novoy = y+somay;

    if(!ehvalida(&m, novox, novoy)) return;
    if(ehparede(&m, novox, novoy)) return;

    m.mapa[novox][novoy] = VAZIO;
    explodepilula2(novox, novoy, somax, somay, qtd-1);
}

int main(){
	
	lemapa(&m);
	encontramapa(&m, &h, HEROI);

	do{
		printf("Pilula: %s\n", (tempilula ? "SIM" : "NAO"));
		imprimemapa(&m);
		char comando;
		scanf(" %c", &comando);
		if(ehdirecao(comando)){			
			move(comando);
		}
		if(comando == BOMBA){
			explodepilula();
			Sleep(2000);
		}
		fantasma();
		system("cls");
	}while(!acabou());	
	
	liberamapa(&m);
	system("pause");
}