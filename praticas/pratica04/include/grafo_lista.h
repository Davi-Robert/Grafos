#ifndef GRAFO_LISTA_H
#define GRAFO_LISTA_H

typedef struct No{
    int vertice;
    // char cor;
    struct No* prox;
} No;

typedef struct GrafoLista{
    int eh_orientado;
    int capacidade;
    No** lista;
} GrafoLista;

GrafoLista* criar_grafo(int capacidade, int eh_orientado);
void inserir_aresta(GrafoLista* grafo, int u, int v);
void inserir_arco(GrafoLista* grafo, int u, int v);
void remover_aresta(GrafoLista* grafo, int u, int v);
void remover_arco(GrafoLista* grafo, int u, int v);
int grau(GrafoLista* grafo, int vertice);
int sao_adjacentes(GrafoLista* grafo, int u, int v);
void exibir(GrafoLista* grafo);
// void resetar_cor(GrafoLista* grafo);
void liberar_grafo(GrafoLista** grafo);

int eh_dag(GrafoLista *grafo);
int* ordenacao_topologica_kahn(GrafoLista *grafo);
No** ordenacao_topologica_dfs(GrafoLista *grafo);


#endif