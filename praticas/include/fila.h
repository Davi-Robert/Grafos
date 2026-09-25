#include "./grafo_lista.h"

#ifndef FILA_H
#define FILA_H

typedef struct Fila{
    int front, tamanho;
    No* fim;
    No* dados;
} Fila;

Fila* criar_fila();
void enqueue(Fila* fila, int dado);
int dequeue(Fila* fila);
int front(Fila* fila);
void liberar_fila(Fila **fila);

#endif