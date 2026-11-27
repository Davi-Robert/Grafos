#ifndef COBERTURA_H
#define COBERTURA_H

typedef struct No {
    int vertice;
    int distancia;
    struct No *proximo;
} No;

typedef struct {
    No** lista;
    int capacidade;
} GrafoListaPonderado;

typedef struct {
    int u, v, peso;
} Aresta;

// cobertura_minima_bt(...) — backtracking com poda por limite.
int cobertura_minima_bt(GrafoListaPonderado *g, int **melhor_cobertura);

// cobertura_gulosa(...) — seleciona vértice de maior grau restante.
int cobertura_gulosa(GrafoListaPonderado *g, int **cobertura);

// eh_cobertura(...) — verifica se todas as arestas estão cobertas.
int eh_cobertura(GrafoListaPonderado *g, int *vertices, int vertices_size);


#endif