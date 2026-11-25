#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H


typedef struct No {
    int vertice;
    int distancia;
    struct No *proximo;
}No;

typedef struct {
    No** lista;
    int capacidade;
}GrafoListaPonderado;

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_ciclo_negativo(int destino, int n, int *pred);
int reconstruir_caminho(int origem, int destino, int *pred);

#endif