#include "./include/grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>

GrafoLista* criar_grafo_lista(int n){
    GrafoLista* grafo = malloc(sizeof(GrafoLista));
    grafo->adj = malloc(n * sizeof(No*));
    grafo->n = n;
    for(int i = 0; i < n; i ++){
        grafo->adj[i] = NULL;
    }
    return grafo;
}
int inserir_aresta_lista(GrafoLista* grafo, int u, int v){
    No* aux;
    No* vertice = malloc(sizeof(No));
    vertice->destino = v;
    vertice->prox = NULL;
    int next_null = -1;
    for(int i = 0;  i < grafo->n; i++){
        if(grafo->adj[i] == NULL){
            if(next_null == -1) next_null = i;
        }else{
            if(grafo->adj[i]->destino == u){
                aux = grafo->adj[i];
                while (aux->prox != NULL){
                    if(aux->destino == v) {
                        printf("Essa aresta já existe");
                        free(vertice);
                        return -1;
                    }
                    aux = aux->prox;
                }
                aux->prox = vertice;
                return 1;
            }
        }
    }
    if(next_null != -1){
        No* vertice_inicio = malloc(sizeof(No));
        vertice_inicio->destino = u;
        vertice_inicio->prox = vertice;
        grafo->adj[next_null] = vertice_inicio;
        
        return 1;
    }
    free(vertice);
    return -1;
}
int remover_aresta_lista(GrafoLista* grafo, int u, int v){
    No *aux, *aux2;
    for(int i = 0;  i < grafo->n; i++){
        if(grafo->adj[i] != NULL){
            if(grafo->adj[i]->destino == u){
                aux = grafo->adj[i];
                if(aux->destino == v){
                    grafo->adj[i] = aux->prox;
                    free(aux);
                    return 1;
                }
                while (aux->prox != NULL){
                    if(aux->prox->destino == v){
                        aux2 = aux->prox;
                        aux->prox = aux->prox->prox;
                        free(aux2);
                        return 1;
                    }
                    aux = aux->prox;
                }
                return 1;
            }
        }
    }
    return -1;
}
int grau_lista(GrafoLista* grafo, int vertice){
    No* aux;
    int count_grau = 0;
    for(int i = 0;  i < grafo->n; i++){
        aux = grafo->adj[i];
        while (aux){
            if(grafo->adj[i]->destino == vertice){
                count_grau++;
                if(grafo->adj[i] == aux)count_grau--;
            }else if(aux->destino == vertice){
                count_grau++;
            }
            aux = aux->prox;
        }
    }
    return count_grau;
}

int sao_adjacentes_lista(GrafoLista* grafo, int u, int v){
    No* aux;
    for(int i = 0;  i < grafo->n; i++){
        if(i == u || i == v){
            aux = grafo->adj[i];
            while(aux){
                if(aux->destino == v){
                    printf("Os vertices %d e %d são adjacentes\n",u,v);
                    return 1;
                }
                aux = aux->prox;
            }
        }
    }
    printf("Os vertices %d e %d não são adjacentes\n",u,v);
    return -1;
}


void exibir_lista(GrafoLista* grafo){
    No* aux;
    for(int i = 0; i < grafo-> n; i ++){
        aux = grafo->adj[i];
        if(aux == NULL){
            printf("[ NULL ]\n");
            continue;
        }else{
            printf("[ %d ] -> ", aux->destino);
            aux = aux->prox;
        }
        while (aux){
            printf("%d -> ",aux->destino);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
    printf("\n");
}

void liberar_cadeia_nos(No* no){
    if(!no){
        return;
    }
    liberar_cadeia_nos(no->prox);
    free(no);
}

void liberar_grafo_lista(GrafoLista** grafo){
    for(int i = 0; i < (*grafo)->n ; i++){
        liberar_cadeia_nos((*grafo)->adj[i]);
    }
    free((*grafo)->adj);
    free(*grafo);
    *grafo = NULL;
}