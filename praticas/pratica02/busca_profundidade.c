#include "grafo_lista.h"
#include "busca_profundidade.h"

#include<stdio.h>
#include<stdlib.h>

Pilha* inicializar_pilha(int capacidade);

int dfs_recursiva(GrafoLista *g, int u, int *visitado, Pilha *historico, int *entrada, int *saida, int tempo_entrada){
    if(historico->topo == -1) tempo_entrada = 1;
    int tempo_saida = 0;
    entrada[u] = tempo_entrada;
    visitado[u] = 1;
    historico->dados[historico->topo++] = u;
    No* no = g->lista[u];
    while(no != NULL){
        int v = no->vertice;
        if(!visitado[v]) {
            tempo_saida += dfs_recursiva(g,v,visitado,historico,entrada,saida, tempo_entrada++);
        }
        no = no->prox;
    }
    saida[u] = tempo_saida;
    return tempo_saida + 1;
}

int contar_componentes(GrafoLista *g, int u, Pilha* p){
    int visitado[g->n];
    int num_componentes = 0;
    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            num_componentes++;
            dfs_recursiva(g, i, p);
        }
    }
    return num_componentes;
}

int tem_ciclo(GrafoLista *g){
    printf("tem_ciclo não implementada");
    return g->n;
}


Pilha* inicializar_pilha(int capacidade){
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    if(pilha == NULL){perror("Falha ao inicializar a memória da pilha"); exit(EXIT_FAILURE);}
    pilha->capacidade = capacidade;
    pilha->topo = -1; // valor invalido
    pilha->dados = (int*)calloc(capacidade,sizeof(int));
    return pilha;
}

//Exibe o conteúdo interno da pilha
void exibir_pilha(Pilha* pilha){
    for(int i = 0; i < pilha->capacidade; i++){
        printf("iteração = %d | vertice = %d\n", i, pilha->dados[i]);
    }
}

void resetar_pilha(Pilha* pilha){
    for(int i = 0; i < pilha->capacidade; i++){
        pilha->dados[i] = -1;
    }
}