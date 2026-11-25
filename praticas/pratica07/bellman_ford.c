#include "bellman_ford.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x7FFFFFFF


int relax(int u, int v,int w, int *dist){
    if(dist[u] + w < dist[v]){
        return 1;
    }
    return 0;
}

int bellman_ford(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    for(int i =0; i < g->capacidade; i++){
        dist[i] = INF;
    }
    memset(pred, -1, sizeof(int) * g->capacidade);

    dist[origem -1] = 0;

    for(int i = 0; i < g->capacidade -1; i++){
        for(int j = 0; j < g->capacidade; j++){
            No* no = g->lista[j];
            if(dist[j] == INF) continue;
            while(no != NULL){
                if(relax(j,no->vertice -1, no->distancia, dist)){
                    dist[no->vertice-1] = dist[j] + no->distancia;
                    pred[no->vertice-1] = j + 1;
                }
                no = no->proximo;
            }
        }
    }
    for(int j = 0; j < g->capacidade; j++){
        No* no = g->lista[j];
        if(dist[j] == INF) continue;
        while(no != NULL){
            if(dist[j] + no->distancia < dist[no->vertice -1]){
                return 0;
            }
            no = no->proximo;
        }
    }
    return 1;
}


void reconstruir_ciclo_negativo(int destino, int n, int *pred) {
    int atual = destino;
    for (int i = 0; i < n; i++) {
        if (atual <= 0 || pred[atual - 1] <= 0) {
            printf("[%d] -> fim\n", atual);
            return;
        }
        printf("[%d] -> ", pred[atual - 1]);
        atual = pred[atual - 1];
    }
    puts("...");
}


int reconstruir_caminho(int origem, int destino, int *pred){
    int contagem = 0;
    if(origem != destino) {
        contagem = reconstruir_caminho(origem, pred[destino -1], pred);
    }else{
        printf("Caminho mais curto:\n");
    }
    printf("[%d] -> ",destino);

    return contagem + 1;
}