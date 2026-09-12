#include "grafo_lista.h"
#include "busca_largura.h"

#include<stdio.h>
#include<stdlib.h>



Fila* inicializar_fila(int n);
void enqueue(int n, Fila* f);
int dequeue(Fila *f);
int front(Fila *f);
void liberar_fila(Fila* f);

void bfs(GrafoLista *g, int origem, int *dist, int *pred){
    Fila *fila = inicializar_fila(g->n);
    int visitado[g->n];
    for(int i=0; i< g->n;i++){
        visitado[i] = -1;
        dist[i] = -1;
        pred[i] = -1;
    }
    visitado[origem - 1] = 1;
    enqueue(origem,fila);
    while(fila->inicio < fila->fim){
        int u = dequeue(fila);
        No* no = g->lista[u-1];
        while(no != NULL){
            int vertice = no->vertice - 1;
            if(visitado[vertice] == -1){
                pred[vertice] = u;
                visitado[vertice] = 1;
                enqueue(no->vertice,fila);
            }
            no = no->prox;
        }
    }
    printf("pred: \n");
    for(int j = 0; j < g->n; j++)printf("[%d] ->", pred[j]);
    puts("\n");
    for(int i = 0; i < g->n; i++){
        int count = 0;
        int start = i;
        while(pred[start] != origem -1){
            if(pred[i] == -1){
                count = -1;
                break;
            }
            if(pred[start] == -1){
                break;
            }
            start = pred[start] - 1;
            count ++;
        }
        dist[i] = count;
        dist[origem - 1] = 0;
    }
    printf("dist: \n");
    for(int j = 0; j < g->n; j++)printf("[%d] ->", dist[j]);
    puts("\n");
}
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);


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


Fila* inicializar_fila(int n){
    Fila *fila = (Fila*)malloc(sizeof(Fila));
    fila->capacidade = n;
    fila->dados = calloc(n,sizeof(int));
    fila->inicio = 0;
    fila->fim = 0;
    fila->tamanho = 0;
    return fila;
}

void enqueue(int n, Fila* f){
    if(!f){printf("Fila inexistente\n"); return;}
    if(f->fim + 1 > f->capacidade){printf("A Fila está cheia\n"); return;}
    f->dados[f->fim++] = n;
    f->tamanho++;
}
int dequeue(Fila *f){
    if(!f){printf("Fila inexistente\n"); return -1;}
    if(f->tamanho <= 0){printf("A fila está vazia\n"); return -1;}
    int aux = f->dados[f->inicio];
    for(int i = 0; i < f->fim; i++){
        if(i == f->capacidade)break;
        f->dados[i] = f->dados[i + 1];
    }
    f->tamanho--;
    f->fim--;
    return aux;
}
int front(Fila *f){
    if(!f){printf("Fila inexistente\n"); return -1;}
    if(f->tamanho <= 0){printf("A fila está vazia\n"); return -1;}
    return f->dados[f->inicio];

}
void liberar_fila(Fila* f);