#include "../include/grafo_lista.h"
#include "../include/fila.h"

#include<stdio.h>
#include<stdlib.h>

Fila* criar_fila(){
    Fila* f = (Fila*)malloc(sizeof(Fila));
    if(!f) return NULL;
    f->dados = NULL;
    f->fim = NULL;
    f->tamanho = 0;
    f->front = 0;
    return f;
}
void enqueue(Fila* fila, int dado){
    if(!fila){printf("Fila não recebida\n");return;}
    No* no = (No*)malloc(sizeof(No));
    if(!no){printf("Erro ao alocar memoria para o novo nó\n");return;}

    no->prox = NULL;
    no->vertice = dado;
    if(fila->dados == NULL){
        fila->dados = no;
        fila->fim = no;
    }else{
        fila->fim->prox = no;
        fila->fim = no;
    }

    fila->tamanho++;
}

int dequeue(Fila* fila){
    if(!fila){printf("Fila não recebida\n");return -1;}
    if(fila->dados == NULL || fila->tamanho <= 0){printf("A fila já esta vazia\n");return -1;}
    No* aux = fila->dados;
    fila->dados = fila->dados->prox;
    int dado = aux->vertice;
    free(aux);
    
    fila->tamanho--;
    if(fila->dados != NULL){
        fila->front = fila->dados->vertice;
    }
    else{
        fila->fim = NULL;
        fila->front = 0;
    }

    return dado;
}

int front(Fila* fila){
    if(!fila){printf("Fila não recebida");return -1;}
    if(fila->tamanho <= 0){return -1;}
    return fila->front;
}

void liberar_fila(Fila **fila){
    if(!fila) return;
    No* aux = (*fila)->dados;
    No* aux2 = NULL;
    while(aux){
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    free((*fila));
    fila = NULL;
}