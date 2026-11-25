#include "bellman_ford.h"

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
    if(u <= 0 || u > g->capacidade || v <= 0 || v > g->capacidade) return;
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


    int origem = 1;
    int destino = 6;
    printf("Origem: %d | Destino: %d\n", origem,destino);
    int *dist = (int*)calloc(g->capacidade,sizeof(int));
    int *pred = (int*)calloc(g->capacidade,sizeof(int));
    int resultado = bellman_ford(g, origem, dist, pred);
    
    printf(resultado? "Não tem ciclo\n" : "Tem ciclo\n");

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

    
    if(!resultado){
        printf("reconstrução do ciclo negativo:\n");
        reconstruir_ciclo_negativo(destino,g->capacidade,pred);
    }else{
        reconstruir_caminho(origem,destino,pred);
        puts("[NULL]");
    }

    free(dist);
    free(pred);
    
    
    // exemplo com ciclo negativo:
    
    printf("Exemplo de grafo com ciclo:\n");
    
    GrafoListaPonderado *g2 = init_graph(5);
    
    // Caminho da origem (1) até o ciclo
    insert_edge(g2, 1, 2, 4);
    // Ciclo 2 -> 3 -> 4 -> 2 com peso total negativo:
    insert_edge(g2, 2, 3, 2);
    insert_edge(g2, 3, 4, 1);
    insert_edge(g2, 4, 2, -5); // 2 + 1 - 5 = -2 (Ciclo Negativo!)
    // Vértice 5 saindo do ciclo (uma "cauda")
    insert_edge(g2, 4, 5, 3);
    
    origem = 1;
    destino = 4;
    printf("Origem: %d | Destino: %d\n", origem,destino);
    dist = (int*)calloc(g2->capacidade,sizeof(int));
    pred = (int*)calloc(g2->capacidade,sizeof(int));
    resultado = bellman_ford(g2, origem, dist, pred);
    
    printf(resultado? "Não tem ciclo\n" : "Tem ciclo\n");
    
    printf("distancia: \n");
    for(int i = 0; i < g2->capacidade; i ++){
        printf("%d: [%d] ",i, dist[i]);
    }
    puts("");
    printf("predecessor: \n");
    for(int i = 0; i < g2->capacidade; i ++){
        printf("%d: [%d] ",i, pred[i]);
    }
    puts("");
    
    
    if(!resultado){
        printf("reconstrução do ciclo negativo:\n");
        reconstruir_ciclo_negativo(destino,g2->capacidade,pred);
    }else{
        reconstruir_caminho(origem,destino,pred);
        puts("[NULL]");
    }
    
    
    free(dist);
    free(pred);
    return 0;
}