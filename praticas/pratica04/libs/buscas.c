#include "../include/buscas.h"
#include "../include/pilha.h"
#include "../include/grafo_lista.h"

#include<stdio.h>

void dfs_total(GrafoLista* grafo, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida){
    int tempo_atual = 0;
    for(int i = 0; i < grafo->capacidade; i++){
        if(grafo->lista[i] == NULL)continue;
        if(!visitado[i]){
            tempo_atual = dfs_recursiva(grafo,i + 1,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
    }
}
int dfs_recursiva(GrafoLista* grafo, int u, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida, int tempo_atual){
    if(!grafo || !visitado || !pilha || !tempo_entrada || !tempo_saida)return -1;
    
    tempo_entrada[u - 1] = ++tempo_atual;
    visitado[u - 1] = 1;
    push(pilha, u);
    No* aux = grafo->lista[u -1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            tempo_atual = dfs_recursiva(grafo,aux->vertice,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
        aux = aux->prox;
    }
    tempo_saida[u-1] = ++tempo_atual;
    return tempo_atual;
}