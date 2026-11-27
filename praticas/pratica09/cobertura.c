#include "cobertura.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função auxiliar interna para obter todas as arestas únicas (u < v) do grafo
static Aresta* obter_arestas(GrafoListaPonderado *g, int *num_arestas) {
    int count = 0;
    for (int i = 0; i < g->capacidade; i++) {
        int u = i + 1;
        No *no = g->lista[i];
        while (no != NULL) {
            if (u < no->vertice) {
                count++;
            }
            no = no->proximo;
        }
    }

    Aresta *arestas = (Aresta *)malloc(sizeof(Aresta) * (count > 0 ? count : 1));
    int idx = 0;
    for (int i = 0; i < g->capacidade; i++) {
        int u = i + 1;
        No *no = g->lista[i];
        while (no != NULL) {
            if (u < no->vertice) {
                arestas[idx].u = u;
                arestas[idx].v = no->vertice;
                arestas[idx].peso = no->distancia;
                idx++;
            }
            no = no->proximo;
        }
    }
    *num_arestas = count;
    return arestas;
}

// Função recursiva de backtracking com poda por limite (bound)
static void bt_aux(Aresta *arestas, int num_arestas, int aresta_idx,
                   int *coberto, int tam_atual,
                   int *melhor_tam, int *melhor_solucao, int capacidade) {
    // Poda: se o tamanho atual já for >= o melhor tamanho encontrado, não compensa continuar
    if (tam_atual >= *melhor_tam) {
        return;
    }

    // Avança pelas arestas que já estão cobertas pelos vértices selecionados
    while (aresta_idx < num_arestas &&
           (coberto[arestas[aresta_idx].u] || coberto[arestas[aresta_idx].v])) {
        aresta_idx++;
    }

    // Se todas as arestas estão cobertas, encontramos uma solução melhor
    if (aresta_idx == num_arestas) {
        *melhor_tam = tam_atual;
        int idx = 0;
        for (int v = 1; v <= capacidade; v++) {
            if (coberto[v]) {
                melhor_solucao[idx++] = v;
            }
        }
        return;
    }

    int u = arestas[aresta_idx].u;
    int v = arestas[aresta_idx].v;

    // Ramo 1: Tenta incluir u na cobertura
    coberto[u] = 1;
    bt_aux(arestas, num_arestas, aresta_idx + 1, coberto, tam_atual + 1,
           melhor_tam, melhor_solucao, capacidade);
    coberto[u] = 0; // backtrack

    // Ramo 2: Tenta incluir v na cobertura
    coberto[v] = 1;
    bt_aux(arestas, num_arestas, aresta_idx + 1, coberto, tam_atual + 1,
           melhor_tam, melhor_solucao, capacidade);
    coberto[v] = 0; // backtrack
}

/*
 * cobertura_minima_bt:
 * Encontra a cobertura mínima exata de vértices usando backtracking com poda.
 * Retorna o número de vértices na cobertura mínima e preenche *melhor_cobertura
 * com um array alocado contendo os vértices (o chamador deve liberar com free).
 */
int cobertura_minima_bt(GrafoListaPonderado *g, int **melhor_cobertura) {
    if (!g || g->capacidade <= 0) {
        if (melhor_cobertura) *melhor_cobertura = NULL;
        return 0;
    }

    int num_arestas = 0;
    Aresta *arestas = obter_arestas(g, &num_arestas);

    // Se o grafo não tem arestas, cobertura mínima é vazia (tamanho 0)
    if (num_arestas == 0) {
        free(arestas);
        if (melhor_cobertura) *melhor_cobertura = NULL;
        return 0;
    }

    int *coberto = (int *)calloc(g->capacidade + 1, sizeof(int));
    int *solucao_temp = (int *)calloc(g->capacidade + 1, sizeof(int));
    // Inicializa o limite superior (bound) inicialmente como g->capacidade + 1
    int melhor_tam = g->capacidade + 1;

    bt_aux(arestas, num_arestas, 0, coberto, 0, &melhor_tam, solucao_temp, g->capacidade);

    int *resultado = NULL;
    if (melhor_tam <= g->capacidade && melhor_tam > 0) {
        resultado = (int *)malloc(sizeof(int) * melhor_tam);
        for (int i = 0; i < melhor_tam; i++) {
            resultado[i] = solucao_temp[i];
        }
    }

    if (melhor_cobertura) {
        *melhor_cobertura = resultado;
    } else {
        free(resultado);
    }

    free(coberto);
    free(solucao_temp);
    free(arestas);

    return melhor_tam <= g->capacidade ? melhor_tam : 0;
}

/*
 * cobertura_gulosa:
 * Heurística gulosa que a cada passo seleciona o vértice de maior grau restante
 * (que cobre o maior número de arestas ainda não cobertas).
 * Retorna a quantidade de vértices da cobertura e preenche *cobertura.
 */
int cobertura_gulosa(GrafoListaPonderado *g, int **cobertura) {
    if (!g || g->capacidade <= 0) {
        if (cobertura) *cobertura = NULL;
        return 0;
    }

    int num_arestas = 0;
    Aresta *arestas = obter_arestas(g, &num_arestas);

    if (num_arestas == 0) {
        free(arestas);
        if (cobertura) *cobertura = NULL;
        return 0;
    }

    // aresta_coberta[i] indica se a aresta i já foi coberta
    int *aresta_coberta = (int *)calloc(num_arestas, sizeof(int));
    // selecionado[v] indica se o vértice v já foi incluído na cobertura
    int *selecionado = (int *)calloc(g->capacidade + 1, sizeof(int));
    int *grau_restante = (int *)calloc(g->capacidade + 1, sizeof(int));
    int *resultado_temp = (int *)malloc(sizeof(int) * g->capacidade);

    int arestas_restantes = num_arestas;
    int qtd_selecionados = 0;

    while (arestas_restantes > 0) {
        // Recalcula o grau restante para cada vértice não selecionado
        memset(grau_restante, 0, sizeof(int) * (g->capacidade + 1));
        for (int i = 0; i < num_arestas; i++) {
            if (!aresta_coberta[i]) {
                grau_restante[arestas[i].u]++;
                grau_restante[arestas[i].v]++;
            }
        }

        // Encontra o vértice com maior grau restante
        int melhor_v = -1;
        int max_grau = -1;
        for (int v = 1; v <= g->capacidade; v++) {
            if (!selecionado[v] && grau_restante[v] > max_grau) {
                max_grau = grau_restante[v];
                melhor_v = v;
            }
        }

        if (melhor_v == -1 || max_grau <= 0) {
            break; // Todas as arestas restantes foram cobertas
        }

        // Adiciona o vértice à cobertura
        selecionado[melhor_v] = 1;
        resultado_temp[qtd_selecionados++] = melhor_v;

        // Marca como cobertas todas as arestas incidentes a melhor_v
        for (int i = 0; i < num_arestas; i++) {
            if (!aresta_coberta[i] && (arestas[i].u == melhor_v || arestas[i].v == melhor_v)) {
                aresta_coberta[i] = 1;
                arestas_restantes--;
            }
        }
    }

    int *resultado = NULL;
    if (qtd_selecionados > 0) {
        resultado = (int *)malloc(sizeof(int) * qtd_selecionados);
        for (int i = 0; i < qtd_selecionados; i++) {
            resultado[i] = resultado_temp[i];
        }
    }

    if (cobertura) {
        *cobertura = resultado;
    } else {
        free(resultado);
    }

    free(aresta_coberta);
    free(selecionado);
    free(grau_restante);
    free(resultado_temp);
    free(arestas);

    return qtd_selecionados;
}

// eh_cobertura(...) — verifica se todas as arestas estão cobertas.
int eh_cobertura(GrafoListaPonderado *g, int *vertices, int vertices_size) {
    if (!g) return 0;
    if (vertices_size < 0) return 0;
    if (vertices_size > 0 && !vertices) return 0;

    int *no_conjunto = (int *)calloc(g->capacidade + 1, sizeof(int));
    if (!no_conjunto) return 0;

    for (int j = 0; j < vertices_size; j++) {
        int v = vertices[j];
        if (v >= 1 && v <= g->capacidade) {
            no_conjunto[v] = 1;
        }
    }

    for (int i = 0; i < g->capacidade; i++) {
        int u = i + 1;
        No *no = g->lista[i];
        while (no != NULL) {
            int v = no->vertice;
            if (u <= v) {
                if (!no_conjunto[u] && !no_conjunto[v]) {
                    free(no_conjunto);
                    return 0; // Aresta (u, v) não está coberta
                }
            }
            no = no->proximo;
        }
    }

    free(no_conjunto);
    return 1;
}

