#include "grafo_matriz.h"
#include <stdio.h>

int main(){

    printf("---------------- Matriz Grafo Não Ordenada ----------------\n");
    
    GrafoMatriz* grafo = criar_grafo_matriz(3);
    
    inserir_aresta_matriz(grafo,0,0);
    inserir_aresta_matriz(grafo,0,1);
    inserir_aresta_matriz(grafo,0,2);
    inserir_aresta_matriz(grafo,1,2);
    
    printf("grau do vertice 0: %d\n", grau_matriz(grafo,0));
    printf("grau do vertice 2: %d\n", grau_matriz(grafo,2));
    
    sao_adjacentes_matriz(grafo,0,1);
    
    exibir_matriz(grafo);
    
    remover_aresta_matriz(grafo,0,1);

    sao_adjacentes_matriz(grafo,1,0);
    
    exibir_matriz(grafo);
    
    liberar_grafo_matriz(&grafo);
    
    printf("---------------- Lista Grafo Não Ordenado ----------------");



    return 0;
}