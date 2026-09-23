#include<stdio.h>
#include<stdlib.h>

#include "../include/grafo_lista.h"
#include "../include/buscas.h"


// funções auxiliares:
No* duplicar_no(No* no);
GrafoLista* duplicar_grafo(GrafoLista* grafo);


// funções das praticas:


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

void grau_direcionado(GrafoLista* grafo, int vertice, int *grau_entrada, int* grau_saida){
    if(!grafo || !grau_entrada || !grau_saida) return;
    if(vertice <= 0){printf("Os vertices devem ser maiores que 0\n");return;}
    if(vertice > grafo->capacidade || vertice > grafo->capacidade){printf("O vertice devem ser menor ou igual a %d\n",grafo->capacidade);return;}
    *grau_entrada = 0;
    *grau_saida = 0;
    No* aux = grafo->lista[vertice -1];
    while (aux){
        (*grau_saida)++;
        if(aux->vertice == vertice) (*grau_entrada)++;
        aux = aux->prox;
    }
    for(int i = 0; i < grafo->capacidade; i++){
        if(i == vertice -1)continue;
        aux = grafo->lista[i];
        while(aux){
            if(aux->vertice == vertice)(*grau_entrada)++;
            aux = aux->prox;
        }
    }
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
    puts("");
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


// ----------------------------------------------------------------------------------------------


int eh_dag(GrafoLista *grafo){
    if(!grafo){printf("grafo não recebido\n");return 0;}
    if(grafo->eh_orientado != 1) return 0;
    if(tem_circulo(grafo))return 0;
    return 1;
}

int* ordenacao_topologica_kahn(GrafoLista *grafo){
    if(!grafo){printf("grafo não recebido\n");return NULL;}
    if(!eh_dag(grafo))return NULL;
    GrafoLista *grafo_duplicata = duplicar_grafo(grafo);
    int idx_lista = 0;
    
    int *graus_entrada = (int*)calloc(grafo_duplicata->capacidade, sizeof(int));
    int *graus_saida = (int*)calloc(grafo_duplicata->capacidade, sizeof(int));
    int *visitado = (int*)calloc(grafo_duplicata->capacidade, sizeof(int));
    int* indices_ordenados = (int*)calloc(grafo_duplicata->capacidade, sizeof(int));
        
    Fila* fila = criar_fila(); // vai conter o conteúdo dos vertices com zero de grau de entrada;
    for(int i = 0; i < grafo->capacidade; i ++){
        grau_direcionado(grafo_duplicata,i + 1,graus_entrada + i,graus_saida + i);
        if(graus_entrada[i] == 0)enqueue(fila, i+1);
    }
    
    while(front(fila) != -1){
        int v = dequeue(fila);
        indices_ordenados[idx_lista++] = v;
        
        No* aux = grafo_duplicata->lista[v -1]; 
        while(aux){
            int vertice_atual = aux->vertice;
            if(!visitado[vertice_atual -1]){
                aux = aux->prox;
                remover_arco(grafo_duplicata,v,vertice_atual);
                grau_direcionado(grafo_duplicata,vertice_atual,&graus_entrada[vertice_atual -1],&graus_saida[vertice_atual -1]);
                if(graus_entrada[vertice_atual -1] == 0){
                    enqueue(fila, vertice_atual);
                }
                continue;
            }
            aux = aux->prox;
        }
        visitado[v -1] = 1;
    }
    
    free(visitado); free(graus_entrada); free(graus_saida);
    liberar_grafo(&grafo_duplicata);
    liberar_fila(&fila);
    return indices_ordenados;
}

No** ordenacao_topologica_dfs(GrafoLista *grafo){
    if(!grafo){printf("grafo não recebido\n");return NULL;}
    if(!eh_dag(grafo))return NULL;
    
    int *visitado = (int*)calloc(grafo->capacidade, sizeof(int));
    int *tempo_entrada = (int*)calloc(grafo->capacidade, sizeof(int));
    int *tempo_saida = (int*)calloc(grafo->capacidade, sizeof(int));
    Pilha* pilha = criar_pilha();
    dfs_total(grafo,visitado,pilha,tempo_entrada,tempo_saida);
    
    int maior = 0;
    No** lista = (No**)malloc(sizeof(No*) * grafo->capacidade);
    No* no = NULL, *aux = NULL;
    
    for(int i = 0; i < grafo->capacidade; i ++){
        // busca o maior tempo_saida
        maior = 0;
        for(int j = 0; j < grafo->capacidade; j++){
            if(tempo_saida[j] > tempo_saida[maior]){
                maior = j;
            }
        }
        
        //cancela o maior tempo saida mas mantem o indice
        tempo_saida[maior] = 0;
        if(grafo->lista[maior] == NULL) continue;
        
        //duplica toda a cadeia de nós
        no = duplicar_no(grafo->lista[maior]);
        lista[i] = no;
        aux = no;
        while(aux){
            no = duplicar_no(aux->prox);
            aux->prox = no;
            aux = aux->prox;
        }
    }
    
    free(visitado);
    free(tempo_entrada);
    free(tempo_saida);
    liberar_pilha(&pilha);
    return lista;
}




// ----------------------------------------------------------------------------------------------

No* duplicar_no(No* no){
    if(!no) return NULL;
    No* new_no = (No*)malloc(sizeof(no));
    if(!new_no){perror("Erro ao alocar memória para a duplicata de nó");exit(1);}
    new_no->vertice = no->vertice;
    new_no->prox = no->prox;
    return new_no;
}

GrafoLista* duplicar_grafo(GrafoLista* grafo){
    if(!grafo) return NULL;
    GrafoLista* new_grafo = criar_grafo(grafo->capacidade,grafo->eh_orientado);
    for(int i = 0; i < grafo->capacidade; i++){
        No* no = duplicar_no(grafo->lista[i]);
        new_grafo->lista[i] = no;
        while (no){
            no->prox = duplicar_no(no->prox);
            no = no->prox;
        }
    }
    return new_grafo;
}