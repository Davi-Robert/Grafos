#include "./include/grafo_lista.h"
#include "./include/buscas.h"
#include "./include/pilha.h"

#include <stdio.h>

#define DEFAULT_LENGTH 6

int main(){

    GrafoLista* grafo = criar_grafo(DEFAULT_LENGTH, 1);

    inserir_arco(grafo,1,4);
    inserir_arco(grafo,1,2);
    inserir_arco(grafo,2,5);
    inserir_arco(grafo,3,6);
    inserir_arco(grafo,3,5);
    inserir_arco(grafo,5,4);
    inserir_arco(grafo,4,2);
    inserir_arco(grafo,6,6);

    exibir(grafo);

    int visitado[grafo->capacidade]; 
    int tempo_entrada[grafo->capacidade];
    int tempo_saida[grafo->capacidade];
    for(int i=0; i<grafo->capacidade;i++){
        visitado[i] = 0;
        tempo_saida[i] = 0;
        tempo_entrada[i] = 0;
    }
    Pilha* pilha = criar_pilha();
    dfs_total(grafo,visitado,pilha,tempo_entrada,tempo_saida);
    
    printf("visitado:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("[%d]",visitado[i]);
    printf("\ntempo_entrada:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_entrada[i]);
    printf("\ntempo_saida:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_saida[i]);
    puts("");

    liberar_grafo(&grafo);

    return 0;
}