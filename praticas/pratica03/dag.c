#include "./include/dag.h"
#include "./include/grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    int *dados;
    int inicio, fim, capacidade;
} Fila;

static Fila* inicializar_fila(int capacidade) {
    Fila *f = malloc(sizeof(Fila));
    f->dados = malloc(capacidade * sizeof(int));
    f->inicio = f->fim = 0;
    f->capacidade = capacidade;
    return f;
}

static void fila_enqueue(Fila *f, int v) {
    f->dados[f->fim++] = v;
}

static int fila_dequeue(Fila *f) {
    return f->dados[f->inicio++];
}

static int fila_vazia(Fila *f) {
    return f->inicio >= f->fim;
}

static void fila_liberar(Fila *f) {
    free(f->dados);
    free(f);
}


typedef struct {
    int *dados;
    int topo;
    int capacidade;
} Pilha;

static Pilha* pilha_criar(int capacidade) {
    Pilha *p = malloc(sizeof(Pilha));
    p->dados = malloc(capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

static void pilha_push(Pilha *p, int v) {
    p->dados[++(p->topo)] = v;
}

static int pilha_pop(Pilha *p) {
    return p->dados[(p->topo)--];
}

static void pilha_liberar(Pilha *p) {
    free(p->dados);
    free(p);
}

int eh_dag(GrafoLista *g) {
    if (!g || !g->lista) return 0;
    int n = g->n;

    int *grau_entrada = calloc(n, sizeof(int));
    if (!grau_entrada) return 0;

    for (int i = 0; i < n; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            grau_entrada[no->vertice - 1]++;
            no = no->prox;
        }
    }

    Fila *fila = inicializar_fila(n);
    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) fila_enqueue(fila, i);
    }

    int processados = 0;
    while (!fila_vazia(fila)) {
        int u = fila_dequeue(fila);
        processados++;
        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice - 1;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) fila_enqueue(fila, v);
            no = no->prox;
        }
    }

    fila_liberar(fila);
    free(grau_entrada);

    return processados == n;
}

int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (!g || !g->lista || !tamanho) return NULL;
    int n = g->n;
    *tamanho = 0;

    int *grau_entrada = calloc(n, sizeof(int));
    if (!grau_entrada) return NULL;

    for (int i = 0; i < n; i++) {
        No *no = g->lista[i];
        while (no != NULL) {
            grau_entrada[no->vertice - 1]++;
            no = no->prox;
        }
    }

    Fila *fila = inicializar_fila(n);
    for (int i = 0; i < n; i++) {
        if (grau_entrada[i] == 0) fila_enqueue(fila, i);
    }

    int *ordem = malloc(n * sizeof(int));
    if (!ordem) {
        fila_liberar(fila);
        free(grau_entrada);
        return NULL;
    }

    int idx = 0;
    while (!fila_vazia(fila)) {
        int u = fila_dequeue(fila);
        ordem[idx++] = u + 1;

        No *no = g->lista[u];
        while (no != NULL) {
            int v = no->vertice - 1;
            grau_entrada[v]--;
            if (grau_entrada[v] == 0) fila_enqueue(fila, v);
            no = no->prox;
        }
    }

    fila_liberar(fila);
    free(grau_entrada);

    if (idx != n) {
        free(ordem);
        return NULL;
    }

    *tamanho = idx;
    return ordem;
}

static int dfs_topo_aux(GrafoLista *g, int u, int *estado, Pilha *pilha) {
    estado[u] = 1; 

    No *no = g->lista[u];
    while (no != NULL) {
        int v = no->vertice - 1;
        if (estado[v] == 1) {
            return 0;
        }
        if (estado[v] == 0) {
            if (!dfs_topo_aux(g, v, estado, pilha)) return 0;
        }
        no = no->prox;
    }

    estado[u] = 2;
    pilha_push(pilha, u + 1);
    return 1;
}
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (!g || !g->lista || !tamanho) return NULL;
    int n = g->n;
    *tamanho = 0;

    int *estado = calloc(n, sizeof(int));
    if (!estado) return NULL;

    Pilha *pilha = pilha_criar(n);

    for (int i = 0; i < n; i++) {
        if (estado[i] == 0) {
            if (!dfs_topo_aux(g, i, estado, pilha)) {
                free(estado);
                pilha_liberar(pilha);
                return NULL;
            }
        }
    }

    free(estado);

    int *ordem = malloc(n * sizeof(int));
    if (!ordem) {
        pilha_liberar(pilha);
        return NULL;
    }

    for (int i = 0; i < n; i++) {
        ordem[i] = pilha_pop(pilha);
    }

    pilha_liberar(pilha);
    *tamanho = n;
    return ordem;
}
