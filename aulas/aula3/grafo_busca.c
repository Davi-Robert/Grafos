#include "grafo_lista.h"
#include "grafo_busca.h"

#include<stdio.h>

int pilha[10];
int visitado[10];
int topo = 0;

void dfs(GrafoLista *g, int u, int *p){
    visitado[u] = 1;
    p[topo++] = u;
    No* no = g->lista[u];
    while (no != NULL)
    {
        int v = no->vertice;
        if(!visitado [u]) dfs(g,v,p);
        no = no->proximo;
    }
    topo--;
    

}