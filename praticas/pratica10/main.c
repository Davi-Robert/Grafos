#include "hamiltoniano.h"
#include "tps.h"

#include <stdio.h>
#include <stdlib.h>

static void imprimir_rota(const int *rota, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d%s", rota[i], (i < tamanho - 1) ? " -> " : "\n");
    }
}

int main() {
    int n = 6;
    GrafoListaPonderado *g = init_graph(n);

    // Grafo não-direcionado ponderado
    insert_edge(g, 1, 2, 4);
    insert_edge(g, 1, 3, 2);

    insert_edge(g, 2, 1, 4);
    insert_edge(g, 2, 3, 1);
    insert_edge(g, 2, 4, 5);
    insert_edge(g, 2, 5, 8);

    insert_edge(g, 3, 1, 2);
    insert_edge(g, 3, 2, 1);
    insert_edge(g, 3, 4, 4);
    insert_edge(g, 3, 5, 10);

    insert_edge(g, 4, 2, 5);
    insert_edge(g, 4, 3, 4);
    insert_edge(g, 4, 5, 2);
    insert_edge(g, 4, 6, 1);

    insert_edge(g, 5, 2, 8);
    insert_edge(g, 5, 3, 10);
    insert_edge(g, 5, 4, 2);
    insert_edge(g, 5, 6, 3);

    insert_edge(g, 6, 5, 3);
    insert_edge(g, 6, 4, 1);

    int *caminho = (int *)calloc(n, sizeof(int));
    int *rota = (int *)calloc(n + 1, sizeof(int));

    // 1. Caminho Hamiltoniano (Backtracking)
    printf("=== 1. Caminho Hamiltoniano (Backtracking) ===\n");
    if (encontrar_caminho_hamiltoniano_bt(g, caminho, 0)) {
        printf("Caminho encontrado: ");
        imprimir_rota(caminho, n);
    } else {
        printf("Nenhum caminho hamiltoniano encontrado.\n");
    }

    // 2. Ciclo Hamiltoniano (Backtracking)
    printf("\n=== 2. Ciclo Hamiltoniano (Backtracking) ===\n");
    if (encontrar_caminho_hamiltoniano_bt(g, caminho, 1)) {
        printf("Ciclo encontrado: ");
        for (int i = 0; i < n; i++) {
            printf("%d -> ", caminho[i]);
        }
        printf("%d\n", caminho[0]);
    } else {
        printf("Nenhum ciclo hamiltoniano encontrado.\n");
    }

    // 3. TSP - Força Bruta
    printf("\n=== 3. TSP - Forca Bruta ===\n");
    int custo_fb = tsp_forca_bruta(g, 1, rota);
    if (custo_fb != -1) {
        printf("Melhor rota (origem 1): ");
        imprimir_rota(rota, n + 1);
        printf("Custo minimo: %d\n", custo_fb);
    } else {
        printf("Nao foi possivel encontrar um ciclo TSP valido.\n");
    }

    // 4. TSP - Heurística do Vizinho Mais Próximo
    printf("\n=== 4. TSP - Vizinho Mais Proximo ===\n");
    int custo_vmp = tsp_vizinho_mais_proximo(g, 1, rota);
    if (custo_vmp != -1) {
        printf("Rota construida (origem 1): ");
        imprimir_rota(rota, n + 1);
        printf("Custo total: %d\n", custo_vmp);
    } else {
        printf("Nao foi possivel construir rota.\n");
    }

    // 5. TSP - Heurística de Inserção do Mais Próximo
    printf("\n=== 5. TSP - Insercao do Mais Proximo ===\n");
    int custo_ins = tsp_insercao(g, 1, rota);
    if (custo_ins != -1) {
        printf("Rota por insercao (origem 1): ");
        imprimir_rota(rota, n + 1);
        printf("Custo total: %d\n", custo_ins);
    } else {
        printf("Nao foi possivel construir rota por insercao.\n");
    }

    // 6. Redução Ciclo Hamiltoniano -> TSP (peso 1 existentes, 2 inexistentes)
    printf("\n=== 6. Reducao Grafo para TSP (grafo_para_tsp) ===\n");
    GrafoListaPonderado *g_tsp = grafo_para_tsp(g);
    int custo_red_fb = tsp_forca_bruta(g_tsp, 1, rota);
    printf("Rota no grafo reduzido (Forca Bruta): ");
    imprimir_rota(rota, n + 1);
    printf("Custo no TSP reduzido: %d (n = %d -> %s Ciclo Hamiltoniano)\n",
           custo_red_fb, n, (custo_red_fb == n) ? "Possui" : "Nao possui");

    int custo_red_vmp = tsp_vizinho_mais_proximo(g_tsp, 1, rota);
    printf("Custo no TSP reduzido (Vizinho Mais Proximo): %d | Rota: ", custo_red_vmp);
    imprimir_rota(rota, n + 1);

    int custo_red_ins = tsp_insercao(g_tsp, 1, rota);
    printf("Custo no TSP reduzido (Insercao): %d | Rota: ", custo_red_ins);
    imprimir_rota(rota, n + 1);

    free(caminho);
    free(rota);
    free_graph(g_tsp);
    free_graph(g);

    return 0;
}
