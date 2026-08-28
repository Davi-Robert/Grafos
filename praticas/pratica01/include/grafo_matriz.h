#ifndef GRAFO_MATRIZ_H
#define GRAFO_MATRIZ_H

// Matriz de adjacência
typedef struct {
    int n;
    int **adj;
} GrafoMatriz;

GrafoMatriz criar_grafo_matriz(unsigned int n);
int inserir_aresta_matriz(GrafoMatriz* grafo, unsigned int u, unsigned int v);
int remover_aresta_matriz(GrafoMatriz* grafo, unsigned int u, unsigned int v);
int grau_matriz(GrafoMatriz* grafo, unsigned int vertice);
int sao_adjacentes_matriz(GrafoMatriz* grafo, unsigned int u, unsigned int v);
void exibir_matriz(GrafoMatriz* grafo);
void liberar_grafo_matriz(GrafoMatriz* grafo);


#endif