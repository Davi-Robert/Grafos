#ifndef DAG_H
#define DAG_H

#include "grafo_lista.h"

/*
 * Verifica se o grafo direcionado é um DAG (Grafo Acíclico Direcionado).
 * Retorna 1 se for DAG, 0 se tiver ciclo.
 */
int eh_dag(GrafoLista *g);

/*
 * Ordenação Topológica pelo algoritmo de Kahn (BFS com grau de entrada).
 * Retorna um array alocado dinamicamente com a ordenação e preenche *tamanho.
 * Retorna NULL se o grafo tiver ciclo (não é DAG).
 * O chamador é responsável por liberar o array retornado.
 */
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);

/*
 * Ordenação Topológica pelo algoritmo DFS (empilhamento na saída).
 * Retorna um array alocado dinamicamente com a ordenação e preenche *tamanho.
 * Retorna NULL se o grafo tiver ciclo (não é DAG).
 * O chamador é responsável por liberar o array retornado.
 */
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);

#endif
