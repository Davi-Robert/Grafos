#include "grafo_lista.h"
#include "busca_profundidade.h"

#include<stdio.h>
#include<stdlib.h>

Pilha* inicializar_pilha(int capacidade);
void push(Pilha* p, int value);
int pop(Pilha *p);
int* dados_pilha(Pilha*p);

void dfs_recursiva(GrafoLista *g,int u, int *visitado, Pilha* p){
    if(!g || !visitado){printf("não foi possivel buscar pois os parâmetros estão nulos\n"); return;}
    if(visitado[u-1] != 1) push(p,u);
    visitado[u - 1] = 1;
    No* no = g->lista[u - 1];
    while(no != NULL){
        int v = no->vertice;
        if(!visitado[v - 1])dfs_recursiva(g,v,visitado,p);
        no = no->prox;
    }
}

int dfs_tempo(GrafoLista *g, int u, int *visitado, Pilha* historico, int *entrada, int *saida, int tempo_entrada){
    if(historico->topo == -1) tempo_entrada = 1;
    int tempo_saida = 0;
    entrada[u - 1] = tempo_entrada;
    visitado[u - 1] = 1;
    historico->dados[historico->topo++] = u;
    No* no = g->lista[u - 1];
    while(no != NULL){
        int v = no->vertice;
        if(!visitado[v-1]) {
            tempo_saida += dfs_tempo(g,v,visitado,historico,entrada,saida, tempo_entrada++);
        }
        no = no->prox;
    }
    saida[u - 1] = tempo_saida;
    return tempo_saida + 1;
}

int contar_componentes(GrafoLista *g){
    int num_componentes = 0;
    int visitado[g->n];
    for(int i = 0; i<g->n; i++) {
        visitado[i] = 0;
    }
    
    Pilha *p;
    for (int i = 0; i < g->n; i++) {
        if (!visitado[i] && g->lista[i] != NULL) {
            p = inicializar_pilha(g->n);
            dfs_recursiva(g,i + 1,visitado, p);
            num_componentes++;
            free(p);
        }
    }
    return num_componentes;
}

int tem_ciclo(GrafoLista *g){
    if(!g){printf("Grafo inexistente\n");return 0;}
    No* slow, *fast;
    for(int i = 0; i < g->n; i ++){
        if(g->lista[i] == NULL) continue;
        slow = g->lista[i];
        break;
    }
    if(!slow->prox)return 0;
    fast = slow->prox;
    while(slow->prox && fast->prox){
        if(slow == fast) return 1;
        slow = slow->prox;
        fast = fast->prox->prox;
    }
    return 0;
}


Pilha* inicializar_pilha(int capacidade){
    Pilha* pilha = (Pilha*)malloc(sizeof(Pilha));
    if(pilha == NULL){perror("Falha ao inicializar a memória da pilha"); exit(EXIT_FAILURE);}
    pilha->capacidade = capacidade;
    pilha->topo = 0; // valor invalido
    pilha->dados = (int*)malloc(capacidade * sizeof(int));
    for(int i = 0; i < capacidade; i++)pilha->dados[i] = -1;
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
    pilha->topo = 0;
}

void push (Pilha *p, int value){
    if(!p){perror("Pilha não foi inicializada\n");return;}
    if(value > p->capacidade){printf("Esse nó esta acima da capacidade da pilha\n");return;}
    p->dados[p->topo++] = value;
}

int* dados_pilha(Pilha*p){
    if(!p)return NULL;
    return p->dados;
}

int pop(Pilha *p){
    if(!p){perror("Pilha não foi inicializada\n");return - 1;}
    if(p->topo == -1)return - 1;
    int aux = p->dados[p->topo];
    p->dados[p->topo--] = -1;
    return aux;
}