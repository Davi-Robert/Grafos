#ifndef GRAFO_H
#define GRAFO_H

typedef struct GrafoMatriz{
    int capacidade;
    int **matriz;
} GrafoMatriz;

GrafoMatriz* matriz_criar_grafo(int capacidade);
void matriz_inserir_aresta(GrafoMatriz* grafo, int u, int v);
void matriz_inserir_arco(GrafoMatriz* grafo, int u, int v);
void matriz_remover_aresta(GrafoMatriz* grafo, int u, int v);
void matriz_remover_arco(GrafoMatriz* grafo, int u, int v);
void matriz_exibir(GrafoMatriz* grafo);
void matriz_liberar_grafo(GrafoMatriz** grafo);

#endif