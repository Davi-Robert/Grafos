#include "grafico_matriz.h"
#include <stdio.h>
#include <stdlib.h>

GrafoMatriz criar_grafo_matriz(int n){
    GrafoMatriz* grafo = malloc(sizeof(GrafoMatriz));
    grafo->n = n;
    grafo->adj = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        grafo->adj[n] = malloc(n * sizeof(int));
        for(int j = 0; j< n; j++){
            grafo->adj[i][j] = 0;
        }
    }
}
void inserir_aresta_matriz(GrafoMatriz* grafo, int u, int v){
    if(u >= grafo->n || v >= grafo-> n){
        printf("os valores vão além do tamanho do grafo");
        return;
    }
    grafo->adj[u][v] = 1;
    grafo->adj[v][u] = 1;
}
void remover_aresta_matriz(GrafoMatriz* grafo, int u, int v){
    if(u >= grafo->n || v >= grafo-> n){
        printf("os valores vão além do tamanho do grafo");
        return;
    }
    if(grafo->adj[u][v] == 1 && grafo->adj[v][u] == 1){
        grafo->adj[u][v] = 0;
        grafo->adj[v][u] = 0;
    } else{
        printf("Essa aresta não existe");
    }

}
int grau_matriz(GrafoMatriz* grafo, int vertice);
int sao_adjacentes_matriz(GrafoMatriz* grafo, int u, int v);
void exibir(GrafoMatriz* grafo);
void liberar_grafo_matriz(GrafoMatriz* grafo);