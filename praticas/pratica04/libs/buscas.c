#include "../include/buscas.h"
#include "../include/pilha.h"
#include "../include/grafo_lista.h"

#include<stdio.h>
#include<stdlib.h>

// funções complementares de outras funções:
int dfs_verificacao_circulo(GrafoLista* grafo, int u, int* visitado); // auxilia a função "tem_circulo()"
void dfs_simples(GrafoLista* grafo, int u, int* visitado); // auxilia a função "contar_componentes()"


// funções das atividades:

void dfs_total(GrafoLista* grafo, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida){
    int tempo_atual = 0;
    for(int i = 0; i < grafo->capacidade; i++){
        if(grafo->lista[i] == NULL)continue;
        if(!visitado[i]){
            tempo_atual = dfs_recursiva(grafo,i + 1,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
    }
}
int dfs_recursiva(GrafoLista* grafo, int u, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida, int tempo_atual){
    if(!grafo || !visitado || !pilha || !tempo_entrada || !tempo_saida)return -1;
    
    tempo_entrada[u - 1] = ++tempo_atual;
    visitado[u - 1] = 1;
    push(pilha, u);
    No* aux = grafo->lista[u -1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            tempo_atual = dfs_recursiva(grafo,aux->vertice,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
        aux = aux->prox;
    }
    tempo_saida[u-1] = ++tempo_atual;
    return tempo_atual;
}

void bfs(GrafoLista *grafo, int u, int *visitado, int *distancia, int* predecessor){
    if(!grafo) return;
    int dist = 0;
    distancia[u - 1] = dist;
    predecessor[u - 1] = 0;
    Fila* fila = criar_fila();
    enqueue(fila,u);
    No* aux;
    while(front(fila) != -1){
        int v = dequeue(fila);
        aux = grafo->lista[v - 1];
        dist = distancia[v - 1] + 1;
        while(aux){
            if(!visitado[aux->vertice -1]){
                enqueue(fila, aux->vertice);
                predecessor[aux->vertice - 1] = v;
                distancia[aux->vertice - 1] = dist;
            }
            aux = aux->prox;
        }
        visitado[v -1] = 1;
    }
    liberar_fila(&fila);
}

int eh_bipartido(GrafoLista* grafo){
    if(!grafo) return -1;
    int visitado[grafo->capacidade];
    int distancia[grafo->capacidade];
    int predecessor[grafo->capacidade];
    int cor[grafo->capacidade];
    
    for(int i = 0; i < grafo->capacidade; i++){
        for(int k = 0; k < grafo->capacidade; k++){visitado[k] = 0; distancia[k] = 0; predecessor[k] = 0; cor[k] = 0;}

        bfs(grafo,i + 1,visitado,distancia,predecessor);
        for(int j = 0; j < grafo->capacidade; j++){
            if(distancia[j] == 0)continue;
            else if(distancia[j] % 2 == 0)cor[j] = 1;
            else cor[j] = 2;
        }

        for(int j = 0; j < grafo->capacidade; j++){
            if(cor[j] == 0){
                continue;
            }else if(i == j){
                continue;
            }else if(cor[j] == cor[predecessor[j] - 1])return 0;
        }
    }
    
    return 1;
}

int tem_circulo(GrafoLista* grafo){
    if(!grafo) return -1;
    int visitado[grafo->capacidade];
    for(int i = 0; i < grafo->capacidade; i++){
        for(int j = 0; j < grafo->capacidade; j++)visitado[j] = 0;
        if(dfs_verificacao_circulo(grafo, i + 1, visitado) == 1) return 1;
    }
    return 0;
}


int contar_componentes(GrafoLista* grafo){
    if(!grafo) return -1;
    if(grafo->eh_orientado){printf("Essa contagem de componentes serve apenas para grafos não orientados"); return -1;}
    
    int qtd_componentes = 0;
    int* visitado = (int*)calloc(grafo->capacidade, sizeof(int));

    for(int i = 0; i < grafo->capacidade; i++){
        if(!visitado[i]){
            qtd_componentes++;
            dfs_simples(grafo,i+1,visitado);
        }
    }

    free(visitado);
    return qtd_componentes;
}




void dfs_simples(GrafoLista* grafo, int u, int* visitado){
    if(!grafo || !visitado)return;
    visitado[u - 1] = 1;
    No* aux = grafo->lista[u - 1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            dfs_verificacao_circulo(grafo, aux->vertice, visitado);
        }
        aux = aux->prox;
    }
}

int dfs_verificacao_circulo(GrafoLista* grafo, int u, int* visitado){
    if(!grafo || !visitado)return -1;
    visitado[u - 1] = 1;
    No* aux = grafo->lista[u - 1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            dfs_verificacao_circulo(grafo, aux->vertice, visitado);
        }else{
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}