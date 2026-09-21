#include "./include/grafo_lista.h"
#include "./include/dag.h"
#include <stdio.h>
#include <stdlib.h>

static void exibir_ordenacao(int *ord, int tamanho) {
    if (!ord) {
        printf("Tem ciclo! Não foi possivel realizar a ordenação topológica\n");
        return;
    }
    printf("  -> ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d", ord[i]);
        if (i < tamanho - 1) printf(" -> ");
    }
    printf("\n");
}

int main(void) {
    GrafoLista *dag = criar_grafo(6);
    inserir_aresta(dag, 6, 3);
    inserir_aresta(dag, 6, 1);
    inserir_aresta(dag, 5, 1);
    inserir_aresta(dag, 5, 2);
    inserir_aresta(dag, 3, 4);
    inserir_aresta(dag, 4, 2);

    printf("\nLista de Adjacência:\n");
    exibir(dag);

    if(eh_dag(dag)){
        printf("É dag\n");
    }else{
        printf("Não é dag\n");
    }

    int tam1 = 0;
    int *ord_kahn = ordenacao_topologica_kahn(dag, &tam1);
    printf("Kahn (BFS):\n");
    exibir_ordenacao(ord_kahn, tam1);
    free(ord_kahn);

    int tam2 = 0;
    int *ord_dfs = ordenacao_topologica_dfs(dag, &tam2);
    printf("DFS (pós-ordem):\n");
    exibir_ordenacao(ord_dfs, tam2);
    free(ord_dfs);

    liberar_grafo(&dag);

    GrafoLista *ciclo = criar_grafo(4);
    inserir_aresta(ciclo, 1, 2);
    inserir_aresta(ciclo, 2, 3);
    inserir_aresta(ciclo, 3, 1);
    inserir_aresta(ciclo, 4, 3);

    printf("\nLista de Adjacência:\n");
    exibir(ciclo);

    if(eh_dag(ciclo)){
        printf("É dag\n");
    }else{
        printf("Não é dag\n");
    }

    int tam3 = 0;
    int *ord_kahn2 = ordenacao_topologica_kahn(ciclo, &tam3);
    printf("Kahn (BFS):\n");
    exibir_ordenacao(ord_kahn2, tam3);
    free(ord_kahn2);

    int tam4 = 0;
    int *ord_dfs2 = ordenacao_topologica_dfs(ciclo, &tam4);
    printf("DFS (pós-ordem):\n");
    exibir_ordenacao(ord_dfs2, tam4);
    free(ord_dfs2);

    liberar_grafo(&ciclo);

    return 0;
}
