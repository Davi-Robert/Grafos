#include "./include/grafo_lista.h"
#include "./include/busca_profundidade.h"

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 5

int main(){
    GrafoLista* grafo = criar_grafo(LENGTH);

    inserir_aresta(grafo,0,1);
    inserir_aresta(grafo,0,2);
    inserir_aresta(grafo,1,3);
    inserir_aresta(grafo,2,3);
    inserir_aresta(grafo,3,4);


    exibir(grafo);


    Pilha* pilha = inicializar_pilha(LENGTH);
    int *visitado = (int*)calloc(LENGTH, sizeof(int));
    dfs_recursiva(grafo, 0, visitado, pilha);

    printf("historico da pilha:\n");
    exibir_pilha(pilha);

    printf("%d\n", eh_bipartido(grafo));
    if(eh_bipartido(grafo)){
        printf("O grafo é bipartido\n");
    }else{
        printf("O grafo não bipartido\n");

    }

    
    liberar_grafo(&grafo);

    return 0;
}