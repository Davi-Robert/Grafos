#include<stdio.h>
#include<stdlib.h>

#include "grafo_lista.h"


GrafoLista* criar_grafo(int n){
    GrafoLista* g = (GrafoLista*)malloc(sizeof(GrafoLista));
    g->lista = (No **)malloc(sizeof(No*)*n);
    for(int i = 0; i< n; i++){
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v){
    No *no = (No*)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = g->lista[u];
    g->lista[u] = no;

    
    No *no2 = (No*)malloc(sizeof(No));
    no2->vertice = u;
    no2->proximo = g->lista[v];
    g->lista[v] = no2;
}
