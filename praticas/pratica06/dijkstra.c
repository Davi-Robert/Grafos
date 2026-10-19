#include "dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void order_heap(MinHeap *heap){
    NoHeap* dados = heap->dados;
    for(int i = heap->tamanho/2-1; i >= 0; i--){
        int menor = i;
        int idx = i;
        while(menor < heap->tamanho){
            int esq = 2 * idx + 1;
            int dir = 2 * idx + 2;

            if(esq < heap->tamanho && dados[esq].distancia < dados[menor].distancia){
                menor = esq;
            }
            if(dir < heap->tamanho && dados[dir].distancia < dados[menor].distancia){
                menor = dir;
            }
            if(menor != idx){
                NoHeap aux = dados[idx];
                dados[idx] = dados[menor];
                dados[menor] = aux;

                heap->posicao[dados[menor].vertice -1] = menor;
                heap->posicao[dados[idx].vertice -1] = idx;

                idx = menor;
            }else{
                break;
            }
        }
    }
}

void insert_heap(MinHeap* heap,int vertex, int distance){
    if(heap == NULL) return;
    if(heap->tamanho == heap->capacidade){
        printf("heap esta lotada\n");
    }
    NoHeap *no = (NoHeap*)malloc(sizeof(NoHeap));
    if(!no)perror("Erro ao alocar memoria na heap");
    no->distancia = distance;no->vertice = vertex;

    heap->dados[heap->tamanho++] = *no;

    order_heap(heap);
}

NoHeap extrair_minimo(MinHeap *heap){
    if(!heap || heap->tamanho <= 0){
        NoHeap no = {-1,-1};
        return no;
    }
    NoHeap aux = heap->dados[0];
    heap->posicao[aux.vertice-1] = -1;
    heap->dados[0] = heap->dados[--heap->tamanho];
    heap->dados[heap->tamanho].distancia = 0; heap->dados[heap->tamanho].vertice = 0;
    order_heap(heap);
    return aux;
}

MinHeap* criar_min_heap(int n){
    if(n <= 0) return NULL;
    MinHeap *no = calloc(1,sizeof(MinHeap));
    no->capacidade = n;
    no->dados = (NoHeap*)calloc(n, sizeof(NoHeap));
    no->posicao = (int*)calloc(n, sizeof(int));
    memset(no->posicao, -1,n * sizeof(int));
    return no;
}

void diminuir_chave(MinHeap *heap, int vertex,int chave){
    if(!heap)return;
    int pos = heap->posicao[vertex -1];
    if(pos != -1) heap->dados[pos].distancia = chave;
    else insert_heap(heap, vertex,chave);
}

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred){
    for(int i = 0; i < g->capacidade; i++){
        dist[i] = 0x7FFFFFFF;
    }
    memset(pred,-1,sizeof(int) * g->capacidade);    
    dist[origem -1] = 0; pred[origem -1] = -1;

    MinHeap *heap = criar_min_heap(g->capacidade);
    insert_heap(heap,origem, 0);

    for(int i = 0; i < g->capacidade; i++){
        NoHeap noheap = extrair_minimo(heap);
        int distance, new_distance;
        No* aux = g->lista[noheap.vertice -1];
        while (aux != NULL){
            distance = dist[aux->vertice-1];
            new_distance = noheap.distancia + aux->distancia;
            if(new_distance < distance){
                pred[aux->vertice -1] = noheap.vertice;
                dist[aux->vertice -1] = noheap.distancia + aux->distancia;
                insert_heap(heap, aux->vertice, aux->distancia + noheap.distancia);         
            }
            aux = aux->proximo;
        }
    }
}


int reconstruir_caminho(int origem, int destino, int *pred){
    int contagem = 0;
    if(origem != destino) {
        contagem = reconstruir_caminho(origem, pred[destino -1], pred);
    }else{
        printf("Caminho mais curto:\n");
    }
    printf("[%d] -> ",destino);

    return contagem + 1;
}