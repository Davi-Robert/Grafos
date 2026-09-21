#include "./include/grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>

GrafoLista* criar_grafo(int n){
    if (n <= 0) return NULL;
    GrafoLista* grafo = malloc(sizeof(GrafoLista));
    if(!grafo){
        perror("erro ao alocar memória para o grafo");
        exit(EXIT_FAILURE);
    }
    grafo->lista = malloc(n * sizeof(No*));
    if(!grafo->lista){
        perror("erro ao alocar memória para a lista de adjacência");
        free(grafo);
        exit(EXIT_FAILURE);
    }
    grafo->n = n;
    for(int i = 0; i < n; i++){
        grafo->lista[i] = NULL;
    }
    return grafo;
}

int inserir_aresta(GrafoLista* grafo, int u, int v){
    if(!grafo || !grafo->lista){
        printf("Grafo inválido ou não inicializado.\n");
        return -1;
    }

    if(u < 1 || u > grafo->n || v < 1 || v > grafo->n){
        printf("não pode inserir vertices menores que 1 ou maiores que %d\n", grafo->n);
        return -1;
    }

    No* aux = grafo->lista[u - 1];
    while(aux != NULL){
        if(aux->vertice == v){
            printf("Essa aresta já existe (%d, %d)\n", u, v);
            return -1;
        }
        aux = aux->prox;
    }

    No* no_v = (No*)malloc(sizeof(No));
    if(!no_v){
        perror("Erro ao alocar memória para o nó");
        return -1;
    }
    no_v->vertice = v;
    no_v->prox = NULL;

    if(grafo->lista[u - 1] == NULL){
        grafo->lista[u - 1] = no_v;
    } else {
        No* tail = grafo->lista[u - 1];
        while(tail->prox != NULL) tail = tail->prox;
        tail->prox = no_v;
    }

    return 1;
}


int remover_aresta(GrafoLista* grafo, int u, int v){
    if(!grafo || !grafo->lista) return -1;
    if(u < 1 || u > grafo->n || v < 1 || v > grafo->n) return -1;

    int removido = 0;

    No* aux = grafo->lista[u - 1];
    No* prev = NULL;
    while(aux != NULL){
        if(aux->vertice == v){
            if(prev == NULL){
                grafo->lista[u - 1] = aux->prox;
            } else {
                prev->prox = aux->prox;
            }
            free(aux);
            removido = 1;
            break;
        }
        prev = aux;
        aux = aux->prox;
    }

    if(u != v){
        aux = grafo->lista[v - 1];
        prev = NULL;
        while(aux != NULL){
            if(aux->vertice == u){
                if(prev == NULL){
                    grafo->lista[v - 1] = aux->prox;
                } else {
                    prev->prox = aux->prox;
                }
                free(aux);
                removido = 1;
                break;
            }
            prev = aux;
            aux = aux->prox;
        }
    }

    return removido ? 1 : -1;
}

int grau(GrafoLista* grafo, int vertice){
    if(!grafo || !grafo->lista || vertice < 1 || vertice > grafo->n) return 0;
    int count = 0;
    No* aux = grafo->lista[vertice - 1];
    while(aux != NULL){
        count++;
        aux = aux->prox;
    }
    return count;
}

int sao_adjacentes(GrafoLista* grafo, int u, int v){
    if(!grafo || !grafo->lista || u < 1 || u > grafo->n || v < 1 || v > grafo->n) return 0;
    No* aux = grafo->lista[u - 1];
    while(aux != NULL){
        if(aux->vertice == v){
            printf("Os vertices %d e %d são adjacentes\n", u, v);
            return 1;
        }
        aux = aux->prox;
    }
    printf("Os vertices %d e %d não são adjacentes\n", u, v);
    return 0;
}

void exibir(GrafoLista* grafo){
    if(!grafo || !grafo->lista) return;
    for(int i = 0; i < grafo->n; i++){
        printf("[%d] -> ", i + 1);
        No* aux = grafo->lista[i];
        while(aux != NULL){
            printf("%d -> ", aux->vertice);
            aux = aux->prox;
        }
        printf("NULL\n");
    }
    printf("\n");
}

void liberar_cadeia_nos(No* no){
    while(no != NULL){
        No* temp = no;
        no = no->prox;
        free(temp);
    }
}

void liberar_grafo(GrafoLista** grafo){
    if(!grafo || !*grafo) return;
    for(int i = 0; i < (*grafo)->n; i++){
        liberar_cadeia_nos((*grafo)->lista[i]);
    }
    free((*grafo)->lista);
    free(*grafo);
    *grafo = NULL;
}