#include<stdio.h>
#include<stdlib.h>

#include "../include/grafo_matriz.h"

// ---------------------------------------- funções pratica 01 ----------------------------------------


GrafoMatriz* matriz_criar_grafo(int capacidade){
    GrafoMatriz *g = (GrafoMatriz*)malloc(sizeof(GrafoMatriz));
    if(!g){
        perror("Não foi possivel alocar memória para o grafo matriz");
        return NULL;
    }
    g->capacidade = capacidade;
    g->matriz = (int**)calloc(capacidade, sizeof(int*));
    if(!g->matriz){
        perror("Não foi possivel alocar memória para a matriz do grafo matriz");
        free(g);
        return NULL;        
    }   
    for(int i = 0; i < capacidade; i ++){
        g->matriz[i] = (int*)calloc(capacidade,sizeof(int));
        if(!g->matriz[i]){
            perror("Não foi possivel alocar memória para uma linha da matriz do grafo matriz");
            for (int j = 0; j < i; j++) {
                free(g->matriz[j]);
            }
            free(g->matriz);
            free(g);
            return NULL;        
        }   
    }
    return g;
}
void matriz_inserir_aresta(GrafoMatriz* grafo, int u, int v){
    if(!grafo){printf("Grafo matriz não recebido\n"); return;}
    if(u <= 0 || v <= 0){printf("Insira vertices maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("O tamanho maximo do grafo para inserção de vertices é %d\n", grafo->capacidade);return;}
    grafo->matriz[u-1][v-1] = 1;
    grafo->matriz[v-1][u-1] = 1;
}
void matriz_inserir_arco(GrafoMatriz* grafo, int u, int v){
    if(!grafo){printf("Grafo matriz não recebido\n"); return;}
    if(u <= 0 || v <= 0){printf("Insira vertices maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("O tamanho maximo do grafo para inserção de vertices é %d\n", grafo->capacidade);return;}
    grafo->matriz[u-1][v-1] = 1;
}
void matriz_remover_aresta(GrafoMatriz* grafo, int u, int v){
    if(!grafo){printf("Grafo matriz não recebido\n"); return;}
    if(u <= 0 || v <= 0){printf("Insira vertices maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("O tamanho maximo do grafo para inserção de vertices é %d\n", grafo->capacidade);return;}
    grafo->matriz[u-1][v-1] = 0;
    grafo->matriz[v-1][u-1] = 0;
}
void matriz_remover_arco(GrafoMatriz* grafo, int u, int v){
    if(!grafo){printf("Grafo matriz não recebido\n"); return;}
    if(u <= 0 || v <= 0){printf("Insira vertices maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("O tamanho maximo do grafo para inserção de vertices é %d\n", grafo->capacidade);return;}
    grafo->matriz[u-1][v-1] = 0;
}
void matriz_exibir(GrafoMatriz* grafo){
    if(!grafo){printf("Grafo matriz não recebido\n"); return;}
    printf("    ");
    for(int i = 0; i < grafo->capacidade; i++) printf("%d ", i + 1);
    puts("");
    for(int i = 0; i < grafo->capacidade; i++){
        for(int j = 0; j < grafo->capacidade; j++){
            if(j == 0){
                printf("%d [ %d ",i + 1,grafo->matriz[i][j]);
            }else if(j == grafo->capacidade - 1){
                printf("%d ]",grafo->matriz[i][j]);
            }else{
                printf("%d ",grafo->matriz[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}
void matriz_liberar_grafo(GrafoMatriz** grafo){
    for(int i = 0; i < (*grafo)->capacidade; i++){
        free((*grafo)->matriz[i]);
    }
    free((*grafo)->matriz);
    free(*grafo);
    grafo = NULL;
}