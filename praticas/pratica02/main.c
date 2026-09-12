#include "./include/grafo_lista.h"
#include "./include/busca_profundidade.h"
#include "busca_largura.h"

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 5

int main()
{
    GrafoLista *grafo = criar_grafo(LENGTH);

    inserir_aresta(grafo, 1, 2);
    inserir_aresta(grafo, 1, 3);
    inserir_aresta(grafo, 2, 4);
    inserir_aresta(grafo, 3, 4);
    inserir_aresta(grafo, 4, 5);

    exibir(grafo);

    int *dist = (int *)calloc(grafo->n, sizeof(int));
    int *pred = (int *)calloc(grafo->n, sizeof(int));

    Pilha *pilha = inicializar_pilha(LENGTH);
    int *visitado = (int *)calloc(LENGTH, sizeof(int));
    int *tempo_entrada = (int *)calloc(LENGTH, sizeof(int));
    int *tempo_saida = (int *)calloc(LENGTH, sizeof(int));

    dfs_recursiva(grafo, 0, visitado, pilha, tempo_entrada, tempo_saida, 0);

    printf("historico da pilha:\n");
    exibir_pilha(pilha);

    printf("%d\n", eh_bipartido(grafo));
    if (eh_bipartido(grafo)){
        printf("O grafo é bipartido\n");
    }else{
        printf("O grafo não bipartido\n");
    }

    bfs(grafo, 1, dist, pred);

    free(visitado);
    free(tempo_entrada);
    free(tempo_saida);
    free(pred);
    free(dist);
    liberar_grafo(&grafo);

    return 0;
}