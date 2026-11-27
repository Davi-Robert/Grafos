#include "tps.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void trocar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Gera todas as (n - 1)! permutações com origem fixa na posição 0
static void permutar_tsp(GrafoListaPonderado *g, int *perm, int inicio, int n,
                         int *melhor_custo, int *melhor_rota) {
    if (inicio == n) {
        int custo_atual = 0;
        for (int i = 0; i < n - 1; i++) {
            int p = peso_aresta(g, perm[i], perm[i + 1]);
            if (p == -1) return; // Aresta inexistente
            custo_atual += p;
        }
        int p_fecho = peso_aresta(g, perm[n - 1], perm[0]);
        if (p_fecho == -1) return; // Não fecha ciclo
        custo_atual += p_fecho;

        if (custo_atual < *melhor_custo) {
            *melhor_custo = custo_atual;
            for (int i = 0; i < n; i++) {
                melhor_rota[i] = perm[i];
            }
            melhor_rota[n] = perm[0];
        }
        return;
    }

    for (int i = inicio; i < n; i++) {
        trocar(&perm[inicio], &perm[i]);
        permutar_tsp(g, perm, inicio + 1, n, melhor_custo, melhor_rota);
        trocar(&perm[inicio], &perm[i]);
    }
}

int tsp_forca_bruta(GrafoListaPonderado *g, int origem, int *melhor_rota) {
    if (!g || g->capacidade <= 0 || !melhor_rota) return -1;
    int n = g->capacidade;
    if (origem <= 0 || origem > n) return -1;

    if (n == 1) {
        melhor_rota[0] = origem;
        melhor_rota[1] = origem;
        return 0;
    }

    int *perm = (int *)malloc(sizeof(int) * n);
    if (!perm) return -1;

    perm[0] = origem;
    int idx = 1;
    for (int v = 1; v <= n; v++) {
        if (v != origem) {
            perm[idx++] = v;
        }
    }

    int melhor_custo = INT_MAX;
    permutar_tsp(g, perm, 1, n, &melhor_custo, melhor_rota);

    free(perm);
    return (melhor_custo == INT_MAX) ? -1 : melhor_custo;
}

// Passo construtivo do vizinho mais próximo (ordena candidatos pelo menor peso)
static int vmp_construir(GrafoListaPonderado *g, int pos, int *rota,
                         int *visitado, int *custo_acumulado) {
    int n = g->capacidade;
    int atual = rota[pos - 1];

    if (pos == n) {
        int p_fecho = peso_aresta(g, atual, rota[0]);
        if (p_fecho == -1) return 0;
        rota[n] = rota[0];
        *custo_acumulado += p_fecho;
        return 1;
    }

    // Coleta vizinhos não visitados alcançáveis a partir de 'atual'
    int *candidatos = (int *)malloc(sizeof(int) * n);
    int *pesos = (int *)malloc(sizeof(int) * n);
    int qtd = 0;

    for (int v = 1; v <= n; v++) {
        if (!visitado[v]) {
            int p = peso_aresta(g, atual, v);
            if (p != -1) {
                candidatos[qtd] = v;
                pesos[qtd] = p;
                qtd++;
            }
        }
    }

    // Ordena candidatos pelo vizinho mais próximo (menor peso primeiro)
    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (pesos[j] < pesos[i]) {
                trocar(&pesos[i], &pesos[j]);
                trocar(&candidatos[i], &candidatos[j]);
            }
        }
    }

    // Tenta o vizinho mais próximo (em grafos completos aceita imediatamente o primeiro)
    for (int i = 0; i < qtd; i++) {
        int prox = candidatos[i];
        int p = pesos[i];

        visitado[prox] = 1;
        rota[pos] = prox;
        *custo_acumulado += p;

        if (vmp_construir(g, pos + 1, rota, visitado, custo_acumulado)) {
            free(candidatos);
            free(pesos);
            return 1;
        }

        *custo_acumulado -= p;
        visitado[prox] = 0;
    }

    free(candidatos);
    free(pesos);
    return 0;
}

int tsp_vizinho_mais_proximo(GrafoListaPonderado *g, int origem, int *rota) {
    if (!g || g->capacidade <= 0 || !rota) return -1;
    int n = g->capacidade;
    if (origem <= 0 || origem > n) return -1;

    if (n == 1) {
        rota[0] = origem;
        rota[1] = origem;
        return 0;
    }

    int *visitado = (int *)calloc(n + 1, sizeof(int));
    if (!visitado) return -1;

    rota[0] = origem;
    visitado[origem] = 1;
    int custo = 0;

    int ok = vmp_construir(g, 1, rota, visitado, &custo);

    free(visitado);
    return ok ? custo : -1;
}

int tsp_insercao(GrafoListaPonderado *g, int origem, int *rota) {
    if (!g || g->capacidade <= 0 || !rota) return -1;
    int n = g->capacidade;
    if (origem <= 0 || origem > n) return -1;

    if (n == 1) {
        rota[0] = origem;
        rota[1] = origem;
        return 0;
    }

    int *na_rota = (int *)calloc(n + 1, sizeof(int));
    if (!na_rota) return -1;

    // 1. Começa com a origem e o vértice mais próximo a ela
    rota[0] = origem;
    na_rota[origem] = 1;
    int tam = 1;

    int mais_prox = -1;
    int menor_dist = INT_MAX;
    for (int v = 1; v <= n; v++) {
        if (!na_rota[v]) {
            int p = peso_aresta(g, origem, v);
            if (p != -1 && p < menor_dist) {
                menor_dist = p;
                mais_prox = v;
            }
        }
    }

    if (mais_prox == -1) {
        free(na_rota);
        return -1;
    }

    rota[1] = mais_prox;
    na_rota[mais_prox] = 1;
    tam = 2;

    // 2. Enquanto houver vértices fora do subciclo, insere o mais próximo
    while (tam < n) {
        int escolhido_k = -1;
        int min_dist_k = INT_MAX;
        int melhor_pos_k = -1;
        int menor_delta_k = INT_MAX;

        // Seleciona o vértice não visitado k mais próximo de algum vértice do subciclo
        // que possua posição válida de inserção entre dois vértices consecutivos (i, j)
        for (int k = 1; k <= n; k++) {
            if (na_rota[k]) continue;

            int dist_k = INT_MAX;
            for (int idx = 0; idx < tam; idx++) {
                int u = rota[idx];
                int p = peso_aresta(g, u, k);
                if (p != -1 && p < dist_k) {
                    dist_k = p;
                }
            }

            if (dist_k == INT_MAX) continue;

            // Encontra a melhor posição (i, j) para inserir k com custo mínimo:
            // delta = peso(i, k) + peso(k, j) - peso(i, j)
            int pos_valida = -1;
            int min_delta = INT_MAX;
            for (int idx = 0; idx < tam; idx++) {
                int u = rota[idx];
                int v = rota[(idx + 1) % tam];
                int p_uk = peso_aresta(g, u, k);
                int p_kv = peso_aresta(g, k, v);
                int p_uv = peso_aresta(g, u, v);

                if (p_uk != -1 && p_kv != -1 && p_uv != -1) {
                    int delta = p_uk + p_kv - p_uv;
                    if (delta < min_delta) {
                        min_delta = delta;
                        pos_valida = idx + 1;
                    }
                }
            }

            if (pos_valida != -1 && dist_k < min_dist_k) {
                min_dist_k = dist_k;
                escolhido_k = k;
                melhor_pos_k = pos_valida;
                menor_delta_k = min_delta;
            }
        }

        (void)menor_delta_k;

        if (escolhido_k == -1) {
            free(na_rota);
            return -1;
        }

        // Insere escolhido_k na posição melhor_pos_k deslocando elementos à direita
        for (int idx = tam; idx > melhor_pos_k; idx--) {
            rota[idx] = rota[idx - 1];
        }
        rota[melhor_pos_k] = escolhido_k;
        na_rota[escolhido_k] = 1;
        tam++;
    }

    // Fecha o ciclo retornando à origem
    rota[n] = rota[0];

    // Calcula o custo total do ciclo construído
    int custo_total = 0;
    for (int i = 0; i < n; i++) {
        int p = peso_aresta(g, rota[i], rota[i + 1]);
        if (p == -1) {
            free(na_rota);
            return -1;
        }
        custo_total += p;
    }

    free(na_rota);
    return custo_total;
}
