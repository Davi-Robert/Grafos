#include "agm.h"

#include <stdio.h>
#include <stdlib.h>

GrafoListaPonderado *init_graph(int n){
    if(n <= 0) return NULL;
    GrafoListaPonderado * g = (GrafoListaPonderado*)calloc(1,sizeof(GrafoListaPonderado));
    g->capacidade = n;
    g->lista = (No**)calloc(n,sizeof(No*));
    return g;
}

void insert_edge(GrafoListaPonderado *g, int u, int v, int distance){
    if(u <= 0 || u > g->capacidade || v <= 0 || v > g->capacidade) return;
    No* no = (No*)calloc(1,sizeof(No));
    no->distancia = distance;
    no->vertice = v;
    no->proximo = g->lista[u-1];
    g->lista[u-1] = no;
}

void free_graph(GrafoListaPonderado *g){
    if(!g) return;
    for(int i = 0; i < g->capacidade; i++){
        No *atual = g->lista[i];
        while(atual != NULL){
            No *temp = atual;
            atual = atual->proximo;
            free(temp);
        }
    }
    free(g->lista);
    free(g);
}

int main(){
    int n = 6;
    GrafoListaPonderado *g = init_graph(n);

    // Grafo não-direcionado ponderado
    insert_edge(g,1,2,4);
    insert_edge(g,1,3,2);

    insert_edge(g,2,1,4);
    insert_edge(g,2,3,1);
    insert_edge(g,2,4,5);
    insert_edge(g,2,5,8);

    insert_edge(g,3,1,2);
    insert_edge(g,3,2,1);
    insert_edge(g,3,4,4);
    insert_edge(g,3,5,10);

    insert_edge(g,4,2,5);
    insert_edge(g,4,3,4);
    insert_edge(g,4,5,2);
    insert_edge(g,4,6,1);

    insert_edge(g,5,2,8);
    insert_edge(g,5,3,10);
    insert_edge(g,5,4,2);
    insert_edge(g,5,6,3);

    insert_edge(g,6,5,3);
    insert_edge(g,6,4,1);

    // 1. KRUSKAL
    int max_arestas = 30;
    int qtd_arestas = 0;
    Aresta* arestas = calloc(max_arestas, sizeof(Aresta));

    for(int i = 0; i < g->capacidade; i++){
        int u = i + 1;
        No* no = g->lista[i];
        while(no != NULL){
            int v = no->vertice;
            if(u < v){
                arestas[qtd_arestas].u = u;
                arestas[qtd_arestas].v = v;
                arestas[qtd_arestas].peso = no->distancia;
                qtd_arestas++;
            }
            no = no->proximo;
        }
    }

    int custo_kruskal = kruskal(g, arestas, qtd_arestas);
    printf("=== KRUSKAL ===\n");
    printf("Custo da AGM: %d\n\n", custo_kruskal);

    // 2. PRIM (com identificação das arestas escolhidas pelo corte)
    Aresta* arestas_prim = malloc((n - 1) * sizeof(Aresta));
    int custo_prim = prim(g, 1, arestas_prim);

    printf("=== PRIM (Propriedade do Corte) ===\n");
    printf("Custo da AGM: %d\n", custo_prim);
    printf("Arestas selecionadas para a AGM:\n");
    for(int i = 0; i < n - 1; i++){
        printf("  (%d - %d) peso: %d\n", arestas_prim[i].u, arestas_prim[i].v, arestas_prim[i].peso);
    }

    free(arestas_prim);
    free(arestas);
    free_graph(g);

    return 0;
}
