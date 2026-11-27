#ifndef HAMILTONIANO_H
#define HAMILTONIANO_H

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

// Funções auxiliares de manipulação do grafo
GrafoListaPonderado *init_graph(int n);
void insert_edge(GrafoListaPonderado *g, int u, int v, int distance);
void free_graph(GrafoListaPonderado *g);
int peso_aresta(GrafoListaPonderado *g, int u, int v);

// encontrar_caminho_hamiltoniano_bt(...) — backtracking com permutações.
// Se fechar_ciclo != 0, exige aresta entre o último e o primeiro vértice (Ciclo Hamiltoniano).
// Preenche 'caminho' (tamanho g->capacidade) e retorna 1 se encontrar, ou 0 caso contrário.
int encontrar_caminho_hamiltoniano_bt(GrafoListaPonderado *g, int *caminho, int fechar_ciclo);

// grafo_para_tsp(...) — redução: peso 1 para arestas existentes, 2 para inexistentes.
GrafoListaPonderado *grafo_para_tsp(GrafoListaPonderado *g);

#endif
