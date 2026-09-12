#include "grafo_lista.h"
#include "busca_profundidade.h"

#include<stdio.h>
#include<stdlib.h>

Pilha* inicializar_pilha(int capacidade);

void dfs_recursiva(GrafoLista *g, int u, int *visitado, Pilha *historico){
    visitado[u] = 1;
    historico->dados[historico->topo++] = u;
    No* no = g->lista[u];
    while(no != NULL){
        int v = no->vertice;
        if(!visitado[v]) dfs_recursiva(g,v,visitado,historico);
        no = no->prox;
    }
}

int eh_bipartido(GrafoLista *g){
    int isBipartido = 1;
    // valores da paridade
    // -1 = não inicializado
    // 0 = par
    // 1 = impar
    int paridade[g->n];
    for(int i = 0; i < g->n; i++) paridade[i] = -1;
    for(int i = 0; i < g->n; i++){
        if(!isBipartido) break;
        if(paridade[i] == -1) paridade[i] = 0;
        No* no = g->lista[i];
        while(no != NULL){
            printf("%d -> ", no->vertice);
            if(g->lista[i] == no){ no = no->prox; continue; }
            else if(paridade[no->vertice] == -1){
                if(paridade[i] == 0) paridade[no->vertice] = 1;
                if(paridade[i] == 1) paridade[no->vertice] = 0;
            }else if(paridade[i] == 1){
                printf("aqui\n");
                // printf("1: %d | %d |\n",i, paridade[no->vertice]);
                if(paridade[no->vertice] == 1) { isBipartido = 0; break; }
            }else if(paridade[i] == 0){
                // printf("1: %d | %d \n",i, paridade[no->vertice]);
                if(paridade[no->vertice] == 0) { isBipartido = 0; break; }
            }
            no = no->prox;
        }
        puts("");
    }
    for(int i = 0; i < g->n; i ++){
        printf("%d: [%d] | ", i, paridade[i]);
    }
    puts("");
    return isBipartido;
}

int contar_componentes(GrafoLista *g){
    return g->n;
}

int tem_ciclo(GrafoLista *g){
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