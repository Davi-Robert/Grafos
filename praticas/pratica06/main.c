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

    insert_edge(g,1,2,5);
    insert_edge(g,1,6,4);

    insert_edge(g,2,5,3);

    insert_edge(g,3,4,5);
    insert_edge(g,3,2,9);
    insert_edge(g,3,1,2);

    insert_edge(g,4,2,8);

    insert_edge(g,6,5,6);


    int origem = 3; int destino = 2;
    int *dist = (int*)calloc(g->capacidade,sizeof(int));
    int *pred = (int*)calloc(g->capacidade,sizeof(int));
    dijkstra(g, 3, dist, pred);

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