#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

// Lista de adjacência
typedef struct No {
    int vertice;
    struct No *prox;
} No;

typedef struct {
    int n;
    No **lista;
} GrafoLista;


GrafoLista* criar_grafo(int n);
int inserir_aresta(GrafoLista* grafo, int u, int v);
int remover_aresta(GrafoLista* grafo, int u, int v);
int grau(GrafoLista* grafo, int vertice);
int sao_adjacentes(GrafoLista* grafo, int u, int v);
void exibir(GrafoLista* grafo);
void liberar_grafo(GrafoLista** grafo);
#endif