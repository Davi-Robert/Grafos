#include "grafo_lista.h"
#include "busca_largura.h"

#include<stdio.h>
#include<stdlib.h>

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