#include "./include/grafo_matriz.h"
#include <stdio.h>

int main(){
    // printf("entrou\n");
    GrafoMatriz grafo = criar_grafo_matriz(6);
    // printf("saiu\n");
    
    // printf("entrou\n");
    inserir_aresta_matriz(&grafo,1,2);
    // printf("saiu\n");
    inserir_aresta_matriz(&grafo,1,3);
    inserir_aresta_matriz(&grafo,1,4);
    inserir_aresta_matriz(&grafo,1,5);
    
    // printf("entrou\n");
    exibir_matriz(&grafo);
    // printf("saiu\n");
    
    remover_aresta_matriz(&grafo,1,4);
    
    printf("\n");
    exibir_matriz(&grafo);

    liberar_grafo_matriz(&grafo);

    return 0;
}