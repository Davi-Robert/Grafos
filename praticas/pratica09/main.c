#include "cobertura.h"

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

    int vertices_size = 2;
    int* cobertura = malloc(sizeof(int) * vertices_size);
    cobertura[0] = 3;
    cobertura[1] = 4;
    
    int is_cover = eh_cobertura(g, cobertura, vertices_size);
    printf("Conjunto {3, 4}: %s\n", is_cover ? "É cobertura" : "Não é cobertura");
    free(cobertura);

    // Teste cobertura gulosa
    int *cob_gulosa = NULL;
    int tam_gulosa = cobertura_gulosa(g, &cob_gulosa);
    printf("\n--- Cobertura Gulosa ---\n");
    printf("Tamanho: %d\nVértices: ", tam_gulosa);
    for (int i = 0; i < tam_gulosa; i++) {
        printf("%d ", cob_gulosa[i]);
    }
    printf("\nVálida: %s\n", eh_cobertura(g, cob_gulosa, tam_gulosa) ? "Sim" : "Não");
    free(cob_gulosa);

    // Teste cobertura mínima com backtracking
    int *cob_bt = NULL;
    int tam_bt = cobertura_minima_bt(g, &cob_bt);
    printf("\n--- Cobertura Mínima (Backtracking) ---\n");
    printf("Tamanho: %d\nVértices: ", tam_bt);
    for (int i = 0; i < tam_bt; i++) {
        printf("%d ", cob_bt[i]);
    }
    printf("\nVálida: %s\n", eh_cobertura(g, cob_bt, tam_bt) ? "Sim" : "Não");
    free(cob_bt);

    free_graph(g);
    return 0;
}