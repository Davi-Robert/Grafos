#include "./include/grafo_lista.h"
#include "./include/grafo_matriz.h"
#include "./include/buscas.h"
#include "./include/pilha.h"

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_LENGTH 6

void write_dot_file(GrafoLista *g, int eh_ordenado);
void liberar_lista(No** no, int tamanho);
void exibir_lista(No** lista, int tamanho);


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

    matriz_liberar_grafo(&grafo_matriz);


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

    eh_dag(grafo_direcionado)?printf("O grafo direcionado é DAG\n"):printf("O grafo direcionado não é DAG\n");
    
    GrafoLista* grafo_direcionado2 = criar_grafo(DEFAULT_LENGTH,1);
    
    inserir_arco(grafo_direcionado2,1,4);
    inserir_arco(grafo_direcionado2,1,2);
    inserir_arco(grafo_direcionado2,3,5);
    inserir_arco(grafo_direcionado2,3,1);
    inserir_arco(grafo_direcionado2,4,2);
    inserir_arco(grafo_direcionado2,5,6);
    inserir_arco(grafo_direcionado2,5,4);
    inserir_arco(grafo_direcionado2,6,2);

    printf("Segundo Grafo Direcionado:\n");
    exibir(grafo_direcionado2);
    
    eh_dag(grafo_direcionado2)?printf("O segundo grafo direcionado é DAG\n"):printf("O segund grafo direcionado não é DAG\n");

    printf("\nORDENAÇÃO TOPOLOGICA DFS:\n\n");
    
    printf("Primeiro grafo direcionado:\n");
    No** ordenacao_dfs1 = ordenacao_topologica_dfs(grafo_direcionado);
    if(!ordenacao_dfs1)printf("O grafo possui um circulo\n");
    else exibir_lista(ordenacao_dfs1, grafo_direcionado->capacidade);
    
    printf("Segundo grafo direcionado:\n");
    No** ordenacao_dfs2 = ordenacao_topologica_dfs(grafo_direcionado2);
    if(!ordenacao_dfs2)printf("O grafo possui um circulo");
    else exibir_lista(ordenacao_dfs2, grafo_direcionado2->capacidade);

    printf("ORDENAÇÃO TOPOLOGICA COM ALGORTIMO DE KAHN (BFS):\n");
    
    printf("Primeiro grafo direcionado:\n");
    int* ordenacao_kahn1 = ordenacao_topologica_kahn(grafo_direcionado);
    if(!ordenacao_kahn1)printf("O grafo possui um circulo\n");
    else for(int i = 0; i < grafo_direcionado->capacidade; i++) printf("[%d]",ordenacao_kahn1[i]);
    puts("");
    
    printf("Segundo grafo direcionado:\n");
    int* ordenacao_kahn2 = ordenacao_topologica_kahn(grafo_direcionado2);
    if(!ordenacao_kahn2)printf("O grafo possui um circulo");
    else for(int i = 0; i < grafo_direcionado2->capacidade; i++) printf("[%d]",ordenacao_kahn2[i]);
    puts("");

    printf("\n\n---------------------------- Pratica 04 ----------------------------\n\n");

    int TAMANHO_GRAFO3 = 7;
    GrafoLista* grafo_direcionado3 = criar_grafo(TAMANHO_GRAFO3,1);
    
    inserir_arco(grafo_direcionado3,1,2);
    inserir_arco(grafo_direcionado3,2,7);
    inserir_arco(grafo_direcionado3,2,6);
    inserir_arco(grafo_direcionado3,2,3);
    inserir_arco(grafo_direcionado3,3,4);
    inserir_arco(grafo_direcionado3,4,3);
    inserir_arco(grafo_direcionado3,5,3);
    inserir_arco(grafo_direcionado3,5,6);
    inserir_arco(grafo_direcionado3,6,5);
    inserir_arco(grafo_direcionado3,7,6);
    inserir_arco(grafo_direcionado3,7,1);
    printf("grafo direcionado 3:\n");
    exibir(grafo_direcionado3);
    
    printf("DFS ARTICULAÇÕES\n");
    int** componentes = (int**)malloc(sizeof(int*) * TAMANHO_GRAFO3);
    for(int i = 0; i < TAMANHO_GRAFO3; i++){
        componentes[i] = (int*)malloc(sizeof(int) * TAMANHO_GRAFO3);
        for(int j = 0; j < TAMANHO_GRAFO3; j++) componentes[i][j] = -1;
    }
    int* low = (int*)calloc(TAMANHO_GRAFO3, sizeof(int));


    int qtd_compontes = dfs_articulacoes(grafo_direcionado3,componentes,low);
    
    for(int i = 0; i < qtd_compontes; i++){
        for(int j = 0; j < TAMANHO_GRAFO3 ; j++) printf("[%d]",componentes[i][j]);
        puts("");
    }

    printf("\nDETECTAR PONTES\n");
    No** pontes = detectar_pontes(grafo_nao_direcionado);
    printf("Pontes no grafo nao direcionado:\n");
    if(pontes){
        for(int i = 0; i < grafo_nao_direcionado->capacidade; i++){
            if(pontes[i]){
                printf("Ponte: (%d, %d)\n", pontes[i]->vertice, pontes[i]->prox->vertice);
            }
        }
        liberar_lista(pontes, grafo_nao_direcionado->capacidade);
    }

    printf("\nPLANARIDADE (EULER / KURATOWSKI)\n");
    if(eh_planar_euler(grafo_nao_direcionado)){
        printf("O primeiro grafo nao direcionado eh planar.\n");
    } else {
        printf("O primeiro grafo nao direcionado nao eh planar.\n");
    }

    GrafoLista* grafo_planar_12 = criar_grafo(12, 0);
    for(int i = 1; i < 12; i++){
        inserir_aresta(grafo_planar_12, i, i + 1);
    }

    inserir_aresta(grafo_planar_12, 1, 3);
    inserir_aresta(grafo_planar_12, 3, 5);
    inserir_aresta(grafo_planar_12, 5, 7);
    inserir_aresta(grafo_planar_12, 7, 9);
    inserir_aresta(grafo_planar_12, 9, 11);

    if(eh_planar_euler(grafo_planar_12)){
        printf("O grafo nao direcionado com 12 vertices eh planar.\n");
    } else {
        printf("O grafo nao direcionado com 12 vertices nao eh planar.\n");
    }

    for(int i = 0; i < TAMANHO_GRAFO3; i++){
        free(componentes[i]);
    }
    free(componentes);
    free(low);
    liberar_grafo(&grafo_direcionado);
    liberar_grafo(&grafo_direcionado2);
    liberar_grafo(&grafo_direcionado3);
    liberar_grafo(&grafo_nao_direcionado);
    liberar_grafo(&grafo_nao_direcionado2);
    liberar_grafo(&grafo_planar_12);

    return 0;
}










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

void liberar_lista(No** no, int tamanho){
    if(!no)return;
    if(tamanho <= 0 ){printf("Tamanho da lista não pode ser menor que zero");return;}
    No* aux, *delete;
    for(int i = 0; i < tamanho; i++){
        aux = no[i];
        while(aux){
            delete = aux;
            aux = aux->prox;
            free(delete);
        }
    }
    free(no);
}

void exibir_lista(No** lista, int tamanho){
    for(int i = 0; i < tamanho; i++){
            No* aux = lista[i];
            printf("%d: ",i+1);
            while(aux){
                printf("[%d] -> ", aux->vertice);
                aux = aux->prox;
            }
            printf("[NULL]\n");
        }
        puts("");
}