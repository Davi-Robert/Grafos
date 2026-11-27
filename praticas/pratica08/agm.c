#include "agm.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

/* =========================================================================
 * KRUSKAL & DSU
 * ========================================================================= */

static int comparar_arestas(const void *a, const void *b) {
    const Aresta *e1 = (const Aresta *)a;
    const Aresta *e2 = (const Aresta *)b;
    return e1->peso - e2->peso;
}

int find(DSU *d, int x) {
    if (x == d->pai[x]) return x;
    d->pai[x] = find(d, d->pai[x]);
    return d->pai[x];
}

int unir(DSU *d, int x, int y) {
    int u = find(d, x);
    int v = find(d, y);
    if (u == v) {
        return 0;
    }

    if (d->rank[u] == d->rank[v]) {
        d->pai[v] = u;
        d->rank[u]++;
    } else if (d->rank[u] < d->rank[v]) {
        d->pai[u] = v;
    } else {
        d->pai[v] = u;
    }
    return 1;
}

int kruskal(GrafoListaPonderado* g, Aresta* arestas, int qtd_arestas) {
    if (!g || !arestas || qtd_arestas <= 0) return 0;

    qsort(arestas, qtd_arestas, sizeof(Aresta), comparar_arestas);

    int n = g->capacidade;
    DSU dsu;
    dsu.n = n;
    dsu.pai = malloc((n + 1) * sizeof(int));
    dsu.rank = calloc(n + 1, sizeof(int));

    for (int i = 0; i <= n; i++) {
        dsu.pai[i] = i;
    }

    int custo = 0;
    int arestas_incluidas = 0;

    for (int i = 0; i < qtd_arestas && arestas_incluidas < n - 1; i++) {
        Aresta aresta = arestas[i];
        if (unir(&dsu, aresta.u, aresta.v)) {
            custo += aresta.peso;
            arestas_incluidas++;
        }
    }

    free(dsu.pai);
    free(dsu.rank);

    return custo;
}

/* =========================================================================
 * PRIM (PROPRIEDADE DO CORTE - BUSCA LINEAR O(V^2))
 *
 * Propriedade do Corte:
 * A cada iteração, temos dois conjuntos de vértices:
 *   S: vértices já na AGM (visitado[v] = 1)
 *   V \ S: vértices ainda fora da AGM (visitado[v] = 0)
 *
 * Selecionamos o vértice fora de S que possui a aresta de MENOR peso cruzando
 * o corte. Pelo lema do corte, essa aresta pertence à AGM.
 * ========================================================================= */

int prim(GrafoListaPonderado* g, int u_inicio, Aresta* arestas_agm) {
    if (!g || g->capacidade <= 0) return 0;

    int n = g->capacidade;
    if (u_inicio < 1 || u_inicio > n) u_inicio = 1;

    int *chave = malloc((n + 1) * sizeof(int));
    int *pai = malloc((n + 1) * sizeof(int));
    int *visitado = calloc(n + 1, sizeof(int)); // 1 se está em S, 0 se em V \ S

    for (int v = 1; v <= n; v++) {
        chave[v] = INF;
        pai[v] = -1;
    }
    chave[u_inicio] = 0; // Vértice raiz começa com custo 0

    int custo_total = 0;
    int count_arestas = 0;

    for (int passo = 0; passo < n; passo++) {
        // 1. Encontra o vértice fora de S com a menor chave (menor aresta cruzando o corte)
        int u = -1;
        int menor_chave = INF;

        for (int v = 1; v <= n; v++) {
            if (!visitado[v] && chave[v] < menor_chave) {
                menor_chave = chave[v];
                u = v;
            }
        }

        // Se nenhum vértice com chave finita foi encontrado, o grafo é desconexo
        if (u == -1 || menor_chave == INF) break;

        // Vértice 'u' entra no conjunto S do corte
        visitado[u] = 1;
        custo_total += chave[u];

        if (pai[u] != -1 && arestas_agm != NULL) {
            arestas_agm[count_arestas].u = pai[u];
            arestas_agm[count_arestas].v = u;
            arestas_agm[count_arestas].peso = chave[u];
            count_arestas++;
        }

        // 2. Atualiza as chaves dos vizinhos de 'u' que ainda estão fora do corte
        No* adj = g->lista[u - 1];
        while (adj != NULL) {
            int v = adj->vertice;
            int peso = adj->distancia;

            if (!visitado[v] && peso < chave[v]) {
                chave[v] = peso;
                pai[v] = u;
            }
            adj = adj->proximo;
        }
    }

    free(chave);
    free(pai);
    free(visitado);

    return custo_total;
}
