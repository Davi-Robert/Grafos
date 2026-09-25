#include "./grafo_lista.h"

#ifndef PILHA_H
#define PILHA_H

typedef struct Pilha{
    int topo, tamanho;
    No* dados;
} Pilha;

Pilha* criar_pilha();
void push(Pilha* pilha, int dado);
int pop(Pilha* pilha);
int top(Pilha* pilha);
void liberar_pilha(Pilha **pilha);

#endif