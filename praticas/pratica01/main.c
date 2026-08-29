#include "./include/grafo_matriz.h"
#include "./include/grafo_lista.h"
#include <stdio.h>

int main(){

    printf("---------------- Matriz Grafo Não Ordenada ----------------\n");
    
    GrafoMatriz* grafo_matriz = criar_grafo_matriz(5);
    
    inserir_aresta_matriz(grafo_matriz,0,1);
    inserir_aresta_matriz(grafo_matriz,0,2);
    inserir_aresta_matriz(grafo_matriz,1,3);
    inserir_aresta_matriz(grafo_matriz,2,3);
    inserir_aresta_matriz(grafo_matriz,3,4);

    printf("grau do vertice 0: %d\n", grau_matriz(grafo_matriz,0));
    printf("grau do vertice 1: %d\n", grau_matriz(grafo_matriz,1));
    printf("grau do vertice 2: %d\n", grau_matriz(grafo_matriz,2));
    printf("grau do vertice 3: %d\n", grau_matriz(grafo_matriz,3));
    printf("grau do vertice 5: %d\n", grau_matriz(grafo_matriz,4));
    
    sao_adjacentes_matriz(grafo_matriz,0,1);
    sao_adjacentes_matriz(grafo_matriz,2,0);
    
    exibir_matriz(grafo_matriz);
    
    remover_aresta_matriz(grafo_matriz,0,1);
    remover_aresta_matriz(grafo_matriz,1,2);

    sao_adjacentes_matriz(grafo_matriz,1,0);
    
    exibir_matriz(grafo_matriz);

    liberar_grafo_matriz(&grafo_matriz);
    
    printf("---------------- Lista Grafo Ordenado ----------------\n");

    GrafoLista* grafo_lista = criar_grafo_lista(5);

    inserir_aresta_lista(grafo_lista,0,1);
    inserir_aresta_lista(grafo_lista,0,2);
    inserir_aresta_lista(grafo_lista,1,3);
    inserir_aresta_lista(grafo_lista,2,3);
    inserir_aresta_lista(grafo_lista,3,4);
 

    exibir_lista(grafo_lista);

    printf("grau do vertice 0: %d\n", grau_lista(grafo_lista,0));
    printf("grau do vertice 1: %d\n", grau_lista(grafo_lista,1));
    printf("grau do vertice 2: %d\n", grau_lista(grafo_lista,2));
    printf("grau do vertice 3: %d\n", grau_lista(grafo_lista,3));
    printf("grau do vertice 4: %d\n", grau_lista(grafo_lista,4));
    
    sao_adjacentes_lista(grafo_lista,0,1);
    sao_adjacentes_lista(grafo_lista,2,0);
    
    exibir_lista(grafo_lista);
    
    remover_aresta_lista(grafo_lista,0,1);
    remover_aresta_lista(grafo_lista,1,2);

    sao_adjacentes_lista(grafo_lista,0,1);
    
    exibir_lista(grafo_lista);
    
    liberar_grafo_lista(&grafo_lista);

    return 0;
}