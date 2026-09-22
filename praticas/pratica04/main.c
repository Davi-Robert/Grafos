#include "./include/grafo_lista.h"
#include "./include/buscas.h"
#include "./include/pilha.h"

#include <stdio.h>

#define DEFAULT_LENGTH 6

void write_dot_file(GrafoLista *g, int eh_ordenado){
    if(!g)return;
    FILE* fp = fopen("grafo.dot","w");
    if(!fp){
        perror("falha ao abrir o arquivo grafo.dot");
        return;
    }

    if(eh_ordenado == 1)fprintf(fp,"digraph G1 {\n");
    else fprintf(fp,"graph G1 {\n");
    for(int i = 0; i < g->capacidade; i++){
        if(g->lista[i] == NULL) continue;
        fprintf(fp,"\t%d [shape=\"circle\"]\n", i+1);
    }
    for(int i = 0; i < g->capacidade; i++){
        No* aux = g->lista[i];
        while(aux != NULL){
            if(i + 1 < aux->vertice){
                if(eh_ordenado == 1) fprintf(fp,"\t%d -> %d\n", i + 1, aux->vertice);
                else fprintf(fp,"\t%d -- %d\n", i + 1, aux->vertice);
            }
            aux = aux->prox;
        }
    }
    fprintf(fp,"}\n");
    fclose(fp);
}


int main(){

    GrafoLista* grafo = criar_grafo(DEFAULT_LENGTH, 1);

    inserir_arco(grafo,1,4);
    inserir_arco(grafo,1,2);
    inserir_arco(grafo,2,5);
    inserir_arco(grafo,3,6);
    inserir_arco(grafo,3,5);
    inserir_arco(grafo,5,4);
    inserir_arco(grafo,4,2);
    inserir_arco(grafo,6,6);
    
    exibir(grafo);
    
    // ------------------------------------ dfs ------------------------------------
    printf("\nDFS RECURSIVA:\n\n");
    
    int visitado[grafo->capacidade]; 
    int tempo_entrada[grafo->capacidade];
    int tempo_saida[grafo->capacidade];
    for(int i=0; i<grafo->capacidade;i++){
        visitado[i] = 0;
        tempo_saida[i] = 0;
        tempo_entrada[i] = 0;
    }
    Pilha* pilha = criar_pilha();
    dfs_total(grafo,visitado,pilha,tempo_entrada,tempo_saida);
    
    printf("visitado:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("[%d]",visitado[i]);
    printf("\ntempo_entrada:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_entrada[i]);
    printf("\ntempo_saida:\n");
    for(int i=0; i<grafo->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_saida[i]);
    puts("");
    
    liberar_pilha(&pilha);
    
    // ------------------------------------ bfs ------------------------------------
    printf("\nBFS:\n\n");

    GrafoLista* grafo2 = criar_grafo(DEFAULT_LENGTH,0);

    inserir_aresta(grafo2,1,2);
    inserir_aresta(grafo2,1,3);
    inserir_aresta(grafo2,1,4);
    inserir_aresta(grafo2,2,5);
    inserir_aresta(grafo2,3,6);
    
    exibir(grafo2);

    // int visitado[grafo->capacidade];
    int distancia[grafo2->capacidade];
    int predecessor[grafo2->capacidade];
    for(int i=0; i<grafo2->capacidade;i++){
        visitado[i] = 0;
        distancia[i] = 0;
        predecessor[i] = 0;
    }
    
    bfs(grafo2,1,visitado,distancia,predecessor);
    
    printf("visitado:\n");
    for(int i=0; i<grafo2->capacidade;i++)printf("[%d]",visitado[i]);
    printf("\ndistancia:\n");
    for(int i=0; i<grafo2->capacidade;i++)printf("[%d]",distancia[i]);
    printf("\npredecessor:\n");
    for(int i=0; i<grafo2->capacidade;i++)printf("[%d]",predecessor[i]);
    puts("");
    


    if(eh_bipartido(grafo2))printf("é bipartido\n");
    else printf("não é bipartido\n");


    liberar_grafo(&grafo);
    liberar_grafo(&grafo2);

    return 0;
}