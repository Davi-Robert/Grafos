#include "../include/grafo_lista.h"
#include "../include/pilha.h"

#include<stdio.h>
#include<stdlib.h>

Pilha* criar_pilha(){
    Pilha* p = (Pilha*)malloc(sizeof(Pilha));
    if(!p) return NULL;
    p->dados = NULL;
    p->tamanho = 0;
    p->topo = 0;
    return p;
}
void push(Pilha* pilha, int dado){
    if(!pilha){printf("Pilha não recebida\n");return;}
    No* no = (No*)malloc(sizeof(No));
    if(!no){printf("Erro ao alocar memoria para o novo nó\n");return;}
    no->prox = pilha->dados;
    no->vertice = dado;
    pilha->dados = no;

    pilha->tamanho++;
}
int pop(Pilha* pilha){
    if(!pilha){printf("Pilha não recebida\n");return -1;}
    if(pilha->dados == NULL || pilha->tamanho <= 0){printf("A pilha já esta vazia\n");return -1;}
    No* aux = pilha->dados;
    pilha->dados = pilha->dados->prox;
    int dado = aux->vertice;
    free(aux);

    pilha->tamanho--;
    if(pilha->dados != NULL)pilha->topo = pilha->dados->vertice;
    else pilha->topo = 0;

    return dado;
}

int top(Pilha* pilha){
    if(!pilha){printf("Pilha não recebida");return -1;}
    if(pilha->tamanho <= 0){return -1;}
    return pilha->topo;
}

void liberar_pilha(Pilha **pilha){
    if(!pilha) return;
    No* aux = (*pilha)->dados;
    No* aux2 = NULL;
    while(aux){
        aux2 = aux;
        aux = aux->prox;
        free(aux2);
    }
    free((*pilha));
    pilha = NULL;
}