#include "./include/grafo_lista.h"
#include <stdio.h>
#include <stdlib.h>

GrafoLista* criar_grafo(int n){
    GrafoLista* grafo = malloc(sizeof(GrafoLista));
    if(!grafo){
        perror("erro ao aloca memória para o grafo");
        exit(EXIT_FAILURE);
    }
    grafo->lista = malloc(n * sizeof(No*));
    grafo->n = n;
    for(int i = 0; i < n; i ++){
        grafo->lista[i] = NULL;
    }
    return grafo;
}
int inserir_aresta(GrafoLista* grafo, int u, int v){
    if(u == 0 || v == 0){printf("não pode inserir vertices menores que 1\n"); return -1;}
    No* aux;
    No* vertice = (No*)malloc(sizeof(No));
    vertice->vertice = v;
    vertice->prox = NULL;
    int next_null = -1;
    for(int i = 1;  i < grafo->n; i++){
        if(grafo->lista[i - 1] == NULL){
            if(next_null == -1) next_null = i - 1;
        }else{
            if(grafo->lista[i - 1]->vertice == u){
                aux = grafo->lista[i - 1];
                while (aux->prox != NULL){
                    if(aux->vertice == v) {
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
        vertice_inicio->vertice = u;
        vertice_inicio->prox = vertice;
        grafo->lista[next_null] = vertice_inicio;
        
        return 1;
    }
    free(vertice);
    return -1;
}
int remover_aresta(GrafoLista* grafo, int u, int v){
    No *aux, *aux2;
    for(int i = 0;  i < grafo->n; i++){
        if(grafo->lista[i] != NULL){
            if(grafo->lista[i]->vertice == u){
                aux = grafo->lista[i];
                if(aux->vertice == v){
                    grafo->lista[i] = aux->prox;
                    free(aux);
                    return 1;
                }
                while (aux->prox != NULL){
                    if(aux->prox->vertice == v){
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
int grau(GrafoLista* grafo, int vertice){
    No* aux;
    int count_grau = 0;
    for(int i = 0;  i < grafo->n; i++){
        aux = grafo->lista[i];
        while (aux){
            if(grafo->lista[i]->vertice == vertice){
                count_grau++;
                if(grafo->lista[i] == aux)count_grau--;
            }else if(aux->vertice == vertice){
                count_grau++;
            }
            aux = aux->prox;
        }
    }
    return count_grau;
}

int sao_adjacentes(GrafoLista* grafo, int u, int v){
    No* aux;
    for(int i = 0;  i < grafo->n; i++){
        if(i == u || i == v){
            aux = grafo->lista[i];
            while(aux){
                if(aux->vertice == v){
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


void exibir(GrafoLista* grafo){
    No* aux;
    for(int i = 0; i < grafo-> n; i ++){
        aux = grafo->lista[i];
        if(aux == NULL){
            printf("[ NULL ]\n");
            continue;
        }else{
            printf("[ %d ] -> ", aux->vertice);
            aux = aux->prox;
        }
        while (aux){
            printf("%d -> ",aux->vertice);
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

void liberar_grafo(GrafoLista** grafo){
    for(int i = 0; i < (*grafo)->n ; i++){
        liberar_cadeia_nos((*grafo)->lista[i]);
    }
    free((*grafo)->lista);
    free(*grafo);
    *grafo = NULL;
}