#include "./include/grafo_lista.h"
#include "./include/grafo_matriz.h"
#include "./include/buscas.h"
#include "./include/pilha.h"

#include <stdio.h>

#define DEFAULT_LENGTH 6

void write_dot_file(GrafoLista *g, int eh_ordenado){
    if(!g)return;
    FILE* fp = fopen("grafo_direcionado.dot","w");
    if(!fp){
        perror("falha ao abrir o arquivo grafo_direcionado.dot");
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

    printf("\n\n---------------------------- Pratica 01 ----------------------------\n\n");
    GrafoMatriz* grafo_matriz = matriz_criar_grafo(DEFAULT_LENGTH);

    printf("Grafo Matriz:\n");
    matriz_inserir_arco(grafo_matriz,1,2);
    matriz_inserir_arco(grafo_matriz,3,5);
    matriz_inserir_arco(grafo_matriz,2,6);

    printf("Inserindo arcos 1 -> 2, 3 -> 5 e 2 -> 6 no grafo matriz\n");

    matriz_exibir(grafo_matriz);

    printf("removendo os arcos 1 -> 2 e 3 -> 5 e adicionando as arestas 1 -> 5, 6 -> 3, 2 -> 3\n");

    matriz_remover_arco(grafo_matriz,1,2);
    matriz_remover_arco(grafo_matriz,3,5);

    matriz_inserir_aresta(grafo_matriz,1,5);
    matriz_inserir_aresta(grafo_matriz,6,3);
    matriz_inserir_aresta(grafo_matriz,2,3);

    matriz_exibir(grafo_matriz);


    GrafoLista* grafo_direcionado = criar_grafo(DEFAULT_LENGTH, 1);
    
    inserir_arco(grafo_direcionado,1,4);
    inserir_arco(grafo_direcionado,1,2);
    inserir_arco(grafo_direcionado,2,5);
    inserir_arco(grafo_direcionado,3,6);
    inserir_arco(grafo_direcionado,3,5);
    inserir_arco(grafo_direcionado,5,4);
    inserir_arco(grafo_direcionado,4,2);
    inserir_arco(grafo_direcionado,6,6);
    
    printf("Primeiro Grafo Direcionado:\n");
    exibir(grafo_direcionado);

    remover_arco(grafo_direcionado,1,4);
    remover_arco(grafo_direcionado,1,2);
    remover_arco(grafo_direcionado,2,5);
    
    printf("Removendo arcos 1->4, 1->2 e 2->5:\n");
    exibir(grafo_direcionado);
    
    printf("OBS: Os arcos foram readicionados para o restante da atividade.\n");
    inserir_arco(grafo_direcionado,1,4);
    inserir_arco(grafo_direcionado,1,2);
    inserir_arco(grafo_direcionado,2,5);
    
    printf("\n\n---------------------------- Pratica 02 ----------------------------\n\n");

    // ------------------------------------ dfs ------------------------------------
    printf("\n---------------------------- DFS RECURSIVA ----------------------------\n\n");
    
    int visitado[grafo_direcionado->capacidade]; 
    int tempo_entrada[grafo_direcionado->capacidade];
    int tempo_saida[grafo_direcionado->capacidade];
    for(int i=0; i<grafo_direcionado->capacidade;i++){
        visitado[i] = 0;
        tempo_saida[i] = 0;
        tempo_entrada[i] = 0;
    }
    Pilha* pilha = criar_pilha();
    dfs_total(grafo_direcionado,visitado,pilha,tempo_entrada,tempo_saida);
    
    printf("visitado:\n");
    for(int i=0; i<grafo_direcionado->capacidade;i++)printf("%d: [%d] | ",i+1, visitado[i]);
    printf("\ntempo_entrada:\n");
    for(int i=0; i<grafo_direcionado->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_entrada[i]);
    printf("\ntempo_saida:\n");
    for(int i=0; i<grafo_direcionado->capacidade;i++)printf("%d: [%d] | ",i+1,tempo_saida[i]);
    
    liberar_pilha(&pilha);
    
    // ------------------------------------ bfs ------------------------------------
    printf("\n\n---------------------------- BFS ----------------------------\n\n");    

    GrafoLista* grafo_nao_direcionado = criar_grafo(DEFAULT_LENGTH,0);
    
    inserir_aresta(grafo_nao_direcionado,1,2);
    inserir_aresta(grafo_nao_direcionado,1,3);
    inserir_aresta(grafo_nao_direcionado,1,4);
    inserir_aresta(grafo_nao_direcionado,2,5);
    inserir_aresta(grafo_nao_direcionado,3,6);
    
    printf("Primeiro Grafo Não Direcionado:\n");
    exibir(grafo_nao_direcionado);

    // int visitado[grafo_direcionado->capacidade];
    int distancia[grafo_nao_direcionado->capacidade];
    int predecessor[grafo_nao_direcionado->capacidade];
    for(int i=0; i<grafo_nao_direcionado->capacidade;i++){
        visitado[i] = 0;
        distancia[i] = 0;
        predecessor[i] = 0;
    }
    
    bfs(grafo_nao_direcionado,1,visitado,distancia,predecessor);
    
    printf("visitado:\n");
    for(int i=0; i<grafo_nao_direcionado->capacidade;i++)printf("[%d]",visitado[i]);
    printf("\n\ndistancia:\n");
    for(int i=0; i<grafo_nao_direcionado->capacidade;i++)printf("[%d]",distancia[i]);
    printf("\n\npredecessor:\n");
    for(int i=0; i<grafo_nao_direcionado->capacidade;i++)printf("[%d]",predecessor[i]);

    printf("\n\n-------------------------------------------------------------\n\n");


    printf("grafo_direcionado direcional:\n");
    if(eh_bipartido(grafo_direcionado))printf("É bipartido\n");
    else printf("Não é bipartido\n");
    tem_circulo(grafo_direcionado)? printf("Tem circulo\n"): printf("Não tem circulo\n");
    puts("");


    printf("grafo_direcionado não direcional:\n");
    if(eh_bipartido(grafo_nao_direcionado))printf("É bipartido\n");
    else printf("Não é bipartido\n");
    tem_circulo(grafo_nao_direcionado)? printf("Tem circulo\n"): printf("Não tem circulo\n");
    puts("");
    
    
    GrafoLista* grafo_nao_direcionado2 = criar_grafo(DEFAULT_LENGTH,0);

    inserir_aresta(grafo_nao_direcionado2,1,2);
    inserir_aresta(grafo_nao_direcionado2,3,4);
    inserir_aresta(grafo_nao_direcionado2,5,6);

    printf("Segundo Grafo Não Direcionado:\n");
    exibir(grafo_nao_direcionado2);


    printf("O Primeiro grafo_nao_direcionado possui %d componentes\n", contar_componentes(grafo_nao_direcionado));
    printf("O Segundo grafo_nao_direcionado possui %d componentes\n", contar_componentes(grafo_nao_direcionado2));



    printf("\n\n---------------------------- Pratica 03 ----------------------------\n\n");

    liberar_grafo(&grafo_direcionado);
    liberar_grafo(&grafo_nao_direcionado);
    liberar_grafo(&grafo_nao_direcionado2);

    return 0;
}