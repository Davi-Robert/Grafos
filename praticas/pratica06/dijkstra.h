#ifndef DIJKSTRA_H
#define DIJKSTRA_H

typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade, tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

typedef struct No {
    int vertice;
    int distancia;
    struct No *proximo;
}No;

typedef struct {
    No** lista;
    int capacidade;
}GrafoListaPonderado;

NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertex,int chave);
MinHeap* criar_min_heap(int n);
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
int reconstruir_caminho(int origem, int destino, int *pred);

void insert_heap(MinHeap* heap,int vertex, int distance);

#endif