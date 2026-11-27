#include "hamiltoniano.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GrafoListaPonderado *init_graph(int n) {
    if (n <= 0) return NULL;
    GrafoListaPonderado *g = (GrafoListaPonderado *)calloc(1, sizeof(GrafoListaPonderado));
    g->capacidade = n;
    g->lista = (No **)calloc(n, sizeof(No *));
    return g;
}

void insert_edge(GrafoListaPonderado *g, int u, int v, int distance) {
    if (!g || u <= 0 || u > g->capacidade || v <= 0 || v > g->capacidade) return;
    No *no = (No *)calloc(1, sizeof(No));
    no->distancia = distance;
    no->vertice = v;
    no->proximo = g->lista[u - 1];
    g->lista[u - 1] = no;
}

void free_graph(GrafoListaPonderado *g) {
    if (!g) return;
    for (int i = 0; i < g->capacidade; i++) {
        No *atual = g->lista[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

// Retorna o peso da aresta (u, v), ou -1 se não existir
int peso_aresta(GrafoListaPonderado *g, int u, int v) {
    if (!g || u <= 0 || u > g->capacidade || v <= 0 || v > g->capacidade) return -1;
    No *atual = g->lista[u - 1];
    while (atual != NULL) {
        if (atual->vertice == v) {
            return atual->distancia;
        }
        atual = atual->proximo;
    }
    return -1;
}

// Função recursiva de backtracking para construir permutações válidas
static int bt_hamiltoniano(GrafoListaPonderado *g, int *caminho, int *visitado,
                           int pos, int fechar_ciclo) {
    int n = g->capacidade;

    if (pos == n) {
        if (fechar_ciclo) {
            return peso_aresta(g, caminho[n - 1], caminho[0]) != -1;
        }
        return 1;
    }

    for (int v = 1; v <= n; v++) {
        if (!visitado[v]) {
            if (pos == 0 || peso_aresta(g, caminho[pos - 1], v) != -1) {
                caminho[pos] = v;
                visitado[v] = 1;

                if (bt_hamiltoniano(g, caminho, visitado, pos + 1, fechar_ciclo)) {
                    return 1;
                }

                visitado[v] = 0;
                caminho[pos] = 0;
            }
        }
    }

    return 0;
}

int encontrar_caminho_hamiltoniano_bt(GrafoListaPonderado *g, int *caminho, int fechar_ciclo) {
    if (!g || g->capacidade <= 0 || !caminho) return 0;

    int n = g->capacidade;
    int *visitado = (int *)calloc(n + 1, sizeof(int));
    if (!visitado) return 0;

    int encontrado = 0;
    if (fechar_ciclo) {
        // Para ciclo hamiltoniano, podemos fixar o primeiro vértice em 1
        caminho[0] = 1;
        visitado[1] = 1;
        encontrado = bt_hamiltoniano(g, caminho, visitado, 1, 1);
    } else {
        encontrado = bt_hamiltoniano(g, caminho, visitado, 0, 0);
    }

    free(visitado);
    return encontrado;
}

GrafoListaPonderado *grafo_para_tsp(GrafoListaPonderado *g) {
    if (!g || g->capacidade <= 0) return NULL;

    int n = g->capacidade;
    GrafoListaPonderado *tsp = init_graph(n);
    if (!tsp) return NULL;

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (u != v) {
                int existe = (peso_aresta(g, u, v) != -1);
                insert_edge(tsp, u, v, existe ? 1 : 2);
            }
        }
    }

    return tsp;
}
