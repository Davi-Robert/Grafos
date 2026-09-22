#include "./grafo_lista.h"
#include "./pilha.h"
#include "./fila.h"

#ifndef BUSCAS_H
#define BUSCAS_H

void dfs_total(GrafoLista* grafo, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida);
int dfs_recursiva(GrafoLista* grafo, int u, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida,int tempo_atual);
void bfs(GrafoLista *grafo, int u, int *visitado, int *distancia, int* predecessor);

int eh_bipartido(GrafoLista* grafo);

#endif