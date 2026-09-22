#include<stdio.h>
#include<stdlib.h>

#include "../include/grafo_lista.h"

// se eh_orientado = 1, não poderá realizar as operações de grafos não orientados, a escolha padrão é grafo não orientado
GrafoLista* criar_grafo(int capacidade, int eh_orientado){
    GrafoLista* g = malloc(sizeof(GrafoLista));
    if(!g)return NULL;
    g->lista = (No**)calloc(capacidade,sizeof(No*));
    if(!g->lista){
        free(g);
        return NULL;
    }
    if(eh_orientado != 1){g->eh_orientado = 0;
    }else{ g->eh_orientado = 1; }

    g->capacidade = capacidade;
    return g;
}
void inserir_aresta(GrafoLista* grafo, int u, int v){
    if(!grafo)return;
    if(grafo->eh_orientado == 1){printf("O grafo recebido é orientado, utilize a função inserir_arco() para adicionar arestas\n");return;}
    if(u <= 0 || v <= 0){printf("Os vertices devem ser maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("Os vertices devem ser menor ou igual a %d\n",grafo->capacidade);return;}
    
    //poderia haver um validador de aresta já existente aqui.
    
    No* vertice_u = (No*)malloc(sizeof(No));
    if(vertice_u == NULL){perror("Erro ao alocar memoria para a nova aresta");return;}
    No* vertice_v = (No*)malloc(sizeof(No));
    if(vertice_v == NULL){perror("Erro ao alocar memoria para a nova aresta");return;}
    
    vertice_u->vertice = v;
    // vertice_u->cor = 'b';
    vertice_u->prox = grafo->lista[u-1];
    grafo->lista[u-1] = vertice_u;
    
    vertice_v->vertice = u;
    // vertice_v->cor = 'b';
    vertice_v->prox = grafo->lista[v-1];
    grafo->lista[v-1] = vertice_v;
}

void inserir_arco(GrafoLista* grafo, int u, int v){
    if(!grafo)return;
    if(grafo->eh_orientado == 0){printf("O grafo recebido é não orientado, utilize a função inserir_aresta() para adicionar arestas\n");return;}
    if(u <= 0 || v <= 0){printf("Os vertices devem ser maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("Os vertices devem ser menor ou igual a %d\n",grafo->capacidade);return;}
    
    //poderia haver um validador de aresta já existente aqui.
    
    No* vertice_u = (No*)malloc(sizeof(No));
    if(vertice_u == NULL){perror("Erro ao alocar memoria para a nova aresta");return;}
    
    vertice_u->vertice = v;
    // vertice_u->cor = 'b';
    vertice_u->prox = grafo->lista[u-1];
    grafo->lista[u-1] = vertice_u;
}

void remover_aresta(GrafoLista* grafo, int u, int v){
    if(!grafo)return;
    if(grafo->eh_orientado == 0){printf("O grafo recebido é orientado, utilize a função remover_arco() para remover arestas\n");return;}
    if(u <= 0 || v <= 0){printf("Os vertices devem ser maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("Os vertices devem ser menor ou igual a %d\n",grafo->capacidade);return;}
    
    No *aux = grafo->lista[u - 1];
    No *aux2 = NULL;
    if(!aux)return;
    if(aux->vertice == u){
        grafo->lista[u - 1] = aux->prox;
        free(aux);
        aux = NULL;
    }else{
        while(aux->prox){
            if(aux->prox->vertice == u){
                aux2 = aux->prox;
                aux->prox = aux2->prox;
                free(aux2);
                break;
            }
            aux = aux->prox;
        }
    }
    aux = grafo->lista[v - 1];
    aux2 = NULL;
    if(!aux)return;
    if(aux->vertice == u){
        grafo->lista[v - 1] = aux->prox;
        free(aux);
        aux = NULL;
    }else{
        while(aux->prox){
            if(aux->prox->vertice == u){
                aux2 = aux->prox;
                aux->prox = aux2->prox;
                free(aux2);aux2 = NULL;
                break;
            }
            aux = aux->prox;
        }
    }
}
void remover_arco(GrafoLista* grafo, int u, int v){
    if(!grafo)return;
    if(grafo->eh_orientado == 0){printf("O grafo recebido é não orientado, utilize a função remover_arestas() para remover arestas\n");return;}
    if(u <= 0 || v <= 0){printf("Os vertices devem ser maiores que 0\n");return;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("Os vertices devem ser menor ou igual a %d\n",grafo->capacidade);return;}
    
    No *aux = grafo->lista[u - 1];
    No *aux2 = NULL;
    if(!aux)return;
    if(aux->vertice == v){
        grafo->lista[u - 1] = aux->prox;
        free(aux);
        aux = NULL;
    }else{
        while(aux->prox){
            if(aux->prox->vertice == v){
                aux2 = aux->prox;
                aux->prox = aux2->prox;
                free(aux2);
                break;
            }
            aux = aux->prox;
        }
    }
}

int grau(GrafoLista* grafo, int vertice){
    if(!grafo)return -1;
    if(vertice <= 0){printf("Os vertices devem ser maiores que 0\n");return -1;}
    if(vertice > grafo->capacidade || vertice > grafo->capacidade){printf("O vertice devem ser menor ou igual a %d\n",grafo->capacidade);return -1;}
    
    No* aux = grafo->lista[vertice -1];
    int count = 0;
    while (aux){
        count++;
        if(aux->vertice == vertice)count++;
        aux = aux->prox;
    }
    return count;
}

//-1: erro
// 0: não são adjacentes
// 1: são adjacentes entre si
// 2: u é adjacente de v mas v não é adjacente de u
// 3: v é adjacente de u mas u não é adjacente de v
int sao_adjacentes(GrafoLista* grafo, int u, int v){
    if(!grafo)return -1;
    if(u <= 0 || v <= 0){printf("Os vertices devem ser maiores que 0\n");return -1;}
    if(u > grafo->capacidade || v > grafo->capacidade){printf("Os vertices devem ser menor ou igual a %d\n",grafo->capacidade);return -1;}
    
    No* aux = grafo->lista[u -1];
    if(grafo->eh_orientado == 0){
        while(aux){
            if(aux->vertice == v){
                return 1;
            }
            aux = aux->prox;
        }
    }else{
        int u_v = 0;
        int v_u = 0;
        while(aux){
            if(aux->vertice == v){
               u_v = 1;
            }
            aux = aux->prox;
        }
        aux = grafo->lista[v - 1];
        while(aux){
            if(aux->vertice == v){
                v_u = 1;
            }
            aux = aux->prox;
        }
        if(u_v == 1 && v_u == 1){
            return 1;
        }else if(u_v == 1 && v_u == 0){
            return 2;
        }else if(u_v == 0 && v_u == 1){
            return 3;
        }
    }
    return 0;
}
void exibir(GrafoLista* grafo){
    if(!grafo)return;
    No* aux; 
    for(int i = 0; i < grafo->capacidade; i ++){
        aux = grafo->lista[i];
        printf("%d : ",i + 1);
        while (aux){
            printf("[%d] -> ",aux->vertice);
            aux = aux->prox;
        }
        printf("[NULL]\n");        
    }
}
// void resetar_cor(GrafoLista* grafo){
//     if(!grafo)return;
//     No* aux;
//     for(int i = 0; i < grafo->capacidade; i ++){
//         aux = grafo->lista[i];
//         while (aux){
//             aux->cor = 'b';
//             aux = aux->prox;
//         }
//     }
// }
void liberar_grafo(GrafoLista** grafo){
    if(!grafo)return;
    No* aux, *aux2; 
    for(int i = 0; i < (*grafo)->capacidade; i ++){
        aux = (*grafo)->lista[i];
        while (aux){
            aux2 = aux;
            aux = aux->prox;
            free(aux2);
        }
    }
    free((*grafo)->lista);
    free((*grafo));
    grafo = NULL;
}