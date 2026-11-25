#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int min(int a, int b){
    return a < b? a: b;
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    int INF = 0x7FFFFFFF;
    for(int i = 0; i < g->capacidade; i++){
        dist[i] = INF;
        pred[i] = -1;
    }

    int *processado = calloc(g->capacidade, sizeof(int));
    dist[origem - 1] = 0;

    for(int i = 0; i < g->capacidade; i++){
        // 1. Encontra o vértice u (0-indexado) não processado com menor dist[u]
        int u = -1;
        for(int v = 0; v < g->capacidade; v++){
            if(!processado[v] && (u == -1 || dist[v] < dist[u])){
                u = v;
            }
        }

        // Se não há mais vértices alcançáveis, encerra
        if(u == -1 || dist[u] == INF) break;

        processado[u] = 1;

        // 2. Relaxa as arestas da lista de adjacência de u
        No *no = g->lista[u];
        while(no != NULL){
            int v = no->vertice - 1; // índice 0-based do vizinho
            if(!processado[v] && dist[v] > dist[u] + no->distancia){
                dist[v] = dist[u] + no->distancia;
                pred[v] = u + 1;     // salva predecessor 1-based
            }
            no = no->proximo;
        }
    }

    free(processado);
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

