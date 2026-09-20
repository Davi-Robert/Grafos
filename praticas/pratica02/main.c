#include "./include/grafo_lista.h"
#include "./include/busca_profundidade.h"
#include "./include/busca_largura.h"

#include <stdio.h>
#include <stdlib.h>

#define LENGTH 10

void write_dot_file(GrafoLista *g){
    if(!g)return;
    FILE* fp = fopen("grafo.dot","w");
    if(!fp){
        perror("falha ao abrir o arquivo grafo.dot");
        return;
    }
    fprintf(fp,"graph G1 {\n");
    for(int i = 0; i < g->n; i++){
        if(g->lista[i] == NULL) continue;
        fprintf(fp,"\t%d [shape=\"circle\"]\n", i+1);
    }
    for(int i = 0; i < g->n; i++){
        No* aux = g->lista[i];
        while(aux != NULL){
            if(i + 1 < aux->vertice){
                fprintf(fp,"\t%d -- %d\n", i + 1, aux->vertice);
            }
            aux = aux->prox;
        }
    }
    fprintf(fp,"}\n");
    fclose(fp);
}

int main()
{
    GrafoLista *grafo = criar_grafo(LENGTH);

    inserir_aresta(grafo, 1, 2);
    inserir_aresta(grafo, 1, 3);
    inserir_aresta(grafo, 2, 1);
    inserir_aresta(grafo, 3, 2);
    inserir_aresta(grafo, 5, 4);
    
    inserir_aresta(grafo, 7, 6);
    inserir_aresta(grafo, 6, 7);

    exibir(grafo);
    write_dot_file(grafo);

    int *dist = (int *)calloc(grafo->n, sizeof(int));
    int *pred = (int *)calloc(grafo->n, sizeof(int));

    Pilha *pilha = inicializar_pilha(LENGTH);
    int *visitado = (int *)calloc(LENGTH, sizeof(int));
    int *tempo_entrada = (int *)calloc(LENGTH, sizeof(int));
    int *tempo_saida = (int *)calloc(LENGTH, sizeof(int));

    dfs_tempo(grafo, 1, visitado, pilha, tempo_entrada, tempo_saida, 0);
    for(int i = 0; i < grafo->n; i++){

    }

    if (eh_bipartido(grafo)){
        printf("O grafo é bipartido\n");
    }else{
        printf("O grafo não bipartido\n");
    }
    puts("");
    bfs(grafo, 1, dist, pred);


    printf("O grafo contem %d componetes\n",contar_componentes(grafo));
    
    inserir_aresta(grafo,5,5);


    free(pilha->dados);
    free(pilha);
    free(visitado);
    free(tempo_entrada);
    free(tempo_saida);
    free(pred);
    free(dist);
    liberar_grafo(&grafo);

    return 0;
}