#ifndef AGM_H
#define AGM_H

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
    int *pai, *rank;
    int n;
} DSU;

typedef struct {
    int u, v, peso;
} Aresta;

// Operações DSU
int find(DSU *d, int x);
int unir(DSU *d, int x, int y);

// Algoritmo de Kruskal: O(E log E)
int kruskal(GrafoListaPonderado* g, Aresta* arestas, int qtd_arestas);

// Algoritmo de Prim: O((V + E) log V) baseado na Propriedade de Corte
// u_inicio: vértice raiz de partida (ex: 1)
// arestas_agm: vetor opcional para armazenar as (V - 1) arestas da AGM (pode ser NULL)
int prim(GrafoListaPonderado* g, int u_inicio, Aresta* arestas_agm);

#endif