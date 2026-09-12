#include "grafo_lista.h"

#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

// Pilha (LIFO) para DFS iterativa
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

Pilha* inicializar_pilha(int capacidade);
void exibir_pilha(Pilha* pilha);

void dfs_recursiva(GrafoLista *g, int u, int *visitado, Pilha *historico);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);


#endif