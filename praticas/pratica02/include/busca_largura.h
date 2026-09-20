
#include "grafo_lista.h"

#ifndef BUSCA_LARGURA
#define BUSCA_LARGURA

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);


#endif