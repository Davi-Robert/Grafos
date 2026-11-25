#include "dijkstra.h"

#include <stdio.h>
#include <stdlib.h>

GrafoListaPonderado *init_graph(int n){
    if(n <= 0) return NULL;
    GrafoListaPonderado * g = (GrafoListaPonderado*)calloc(1,sizeof(GrafoListaPonderado));
    g->capacidade = n;
    g->lista = (No**)calloc(n,sizeof(No*));
    return g;
}

void insert_edge(GrafoListaPonderado *g,int u, int v,int distance){
    if(u <= 0 || u > g->capacidade || v <= 0 || v > g->capacidade || distance <= 0) return;
    No* no = (No*)calloc(1,sizeof(No));
    no->distancia = distance;
    no->vertice = v;
    no->proximo = g->lista[u-1];
    g->lista[u-1] = no;
}

int main(){

    GrafoListaPonderado *g = init_graph(6);

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


    int origem = 1; int destino = 6;
    int *dist = (int*)calloc(g->capacidade,sizeof(int));
    int *pred = (int*)calloc(g->capacidade,sizeof(int));
    dijkstra(g, origem, dist, pred);

    printf("distancia: \n");
    for(int i = 0; i < g->capacidade; i ++){
        printf("%d: [%d] ",i, dist[i]);
    }
    puts("");
    printf("predecessor: \n");
    for(int i = 0; i < g->capacidade; i ++){
        printf("%d: [%d] ",i, pred[i]);
    }
    puts("");

    reconstruir_caminho(origem,destino,pred);
    puts("[NULL]");

    return 0;
}