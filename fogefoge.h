#ifndef _FOGEFOGE_H_
#define _FOGEFOGE_H_

#define ESQUERDA 'a'
#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define BOMBA 'b'

int acabou();
void move(char direcao);
void fantasma();
int ondeofantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
int ehdirecao(char direcao);
void explodepilula();
void explodepilula2(int x, int y, int somax, int somay, int qtd);

#endif