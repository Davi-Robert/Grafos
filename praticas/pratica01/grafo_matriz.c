#include "./include/grafo_matriz.h"
#include <stdio.h>
#include <stdlib.h>

GrafoMatriz* criar_grafo_matriz(int n){
    GrafoMatriz* grafo = malloc(sizeof(GrafoMatriz));
    grafo->n = n;
    grafo->adj = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        grafo->adj[i] = malloc(n * sizeof(int));
        for(int j = 0; j< n; j++){
            grafo->adj[i][j] = 0;
        }
    }
    return grafo;
}
int inserir_aresta_matriz(GrafoMatriz* grafo, int u, int v){
    if(u >= grafo->n || v >= grafo-> n){
        printf("os valores vão além do tamanho do grafo. O tamanho do grafo é de até %d\n", grafo->n - 1);
        return -1;
    }else if(!grafo){
        printf("grafo não recebido\n");
        return -1;
    }
    grafo->adj[u][v] = 1;
    grafo->adj[v][u] = 1;
    return 1;
}
int remover_aresta_matriz(GrafoMatriz* grafo, int u, int v){
    if(u >= grafo->n || v >= grafo-> n){
        printf("os valores vão além do tamanho do grafo. O tamanho do grafo é de até %d\n", grafo->n - 1);
        return -1;
    }else if(!grafo){
        printf("grafo não recebido\n");
        return -1;
    }
    if(grafo->adj[u][v] == 1 && grafo->adj[v][u] == 1){
        grafo->adj[u][v] = 0;
        grafo->adj[v][u] = 0;
        return 1;
    } else{
        printf("Essa aresta não existe\n");
        return -1;
    }
    
}
int grau_matriz(GrafoMatriz* grafo, int vertice){
    if(vertice >= grafo->n){
        printf("o vertice vão além do tamanho do grafo. O tamanho maximo do vertice é %d\n", grafo->n - 1);
    return -1;
    }else if(!grafo){
        printf("grafo não recebido\n");
        return -1;
    }
    int count_grau = 0;
    for(int i = 0; i < grafo-> n; i ++){
        if(grafo->adj[i][vertice] == 1) count_grau++;
        if(grafo->adj[vertice][i] == 1) count_grau++;
    }
    return count_grau;
}
int sao_adjacentes_matriz(GrafoMatriz* grafo, int u, int v){
    if(u >= grafo->n || v >= grafo->n){
        printf("os valores vão além do tamanho do grafo. O tamanho maximo do vertice é %d\n", grafo->n - 1);
        return -1;
    }
    if(grafo->adj[u][v] == 1 || grafo->adj[u][v] == 1){
        printf("Os vertices %d e %d são adjacentes\n",u,v);
        return 1;
    }else{
        printf("Os vertices %d e %d não são adjacentes\n",u,v);
        return -1;
    }
    return -1;
}
void exibir_matriz(GrafoMatriz* grafo){
    for(int i = 0; i < grafo-> n; i ++){
       for(int j = 0; j < grafo-> n; j ++){
        if(j == 0){
            printf("[ %d ",grafo->adj[i][j]);
        }else if(j == grafo->n -1){
            printf(" %d ]",grafo->adj[i][j]);
        }else{
            printf(" %d ",grafo->adj[i][j]);
        }
       }
       printf("\n");
    }
    printf("\n");
}
void liberar_grafo_matriz(GrafoMatriz** grafo){
    for(int i = 0; i < (*grafo)->n; i++){
        free((*grafo)->adj[i]);
    }
    free((*grafo)->adj);
    free(*grafo);
    *grafo = NULL;
}