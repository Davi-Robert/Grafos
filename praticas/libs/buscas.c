#include "../include/buscas.h"
#include "../include/pilha.h"
#include "../include/grafo_lista.h"

#include<stdio.h>
#include<stdlib.h>

// funções complementares de outras funções:
int dfs_verificacao_circulo(GrafoLista* grafo, int u, int* visitado); // auxilia a função "tem_circulo()"
void dfs_simples(GrafoLista* grafo, int u, int* visitado); // auxilia a função "contar_componentes()"
void dfs_tarjan(GrafoLista* grafo, int u, Pilha* pilha, int **componentes, int* descoberto, int* low, int* idx_componetes, int* idx_visto);
int min(int number1, int number2);
void dfs_pontes(GrafoLista* grafo, int u, int pai, int* visitado, int* descoberto, int* low, int* timer, No** pontes, int* idx_ponte);
int contar_arestas(GrafoLista* grafo);
int tem_subdivisao_k5(GrafoLista* grafo);
int tem_subdivisao_k33(GrafoLista* grafo);
int tentar_caminhos_disjuntos(GrafoLista* grafo, int pares[][2], int num_pares, int par_atual, int* usado, int* branch, int num_branch);
int dfs_caminho(GrafoLista* grafo, int atual, int destino, int* usado, int* no_caminho, int* branch, int num_branch, int pares[][2], int num_pares, int par_atual);

// ---------------------------------------- funções pratica 02 ----------------------------------------

void dfs_total(GrafoLista* grafo, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida){
    int tempo_atual = 0;
    for(int i = 0; i < grafo->capacidade; i++){
        if(grafo->lista[i] == NULL)continue;
        if(!visitado[i]){
            tempo_atual = dfs_recursiva(grafo,i + 1,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
    }
}
int dfs_recursiva(GrafoLista* grafo, int u, int* visitado, Pilha* pilha, int* tempo_entrada, int* tempo_saida, int tempo_atual){
    if(!grafo || !visitado || !pilha || !tempo_entrada || !tempo_saida)return -1;
    
    tempo_entrada[u - 1] = ++tempo_atual;
    visitado[u - 1] = 1;
    push(pilha, u);
    No* aux = grafo->lista[u -1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            tempo_atual = dfs_recursiva(grafo,aux->vertice,visitado,pilha,tempo_entrada,tempo_saida,tempo_atual);
        }
        aux = aux->prox;
    }
    tempo_saida[u-1] = ++tempo_atual;
    return tempo_atual;
}

void bfs(GrafoLista *grafo, int u, int *visitado, int *distancia, int* predecessor){
    if(!grafo) return;
    int dist = 0;
    distancia[u - 1] = dist;
    predecessor[u - 1] = 0;
    Fila* fila = criar_fila();
    enqueue(fila,u);
    No* aux;
    while(front(fila) != -1){
        int v = dequeue(fila);
        aux = grafo->lista[v - 1];
        dist = distancia[v - 1] + 1;
        while(aux){
            if(!visitado[aux->vertice -1]){
                enqueue(fila, aux->vertice);
                predecessor[aux->vertice - 1] = v;
                distancia[aux->vertice - 1] = dist;
            }
            aux = aux->prox;
        }
        visitado[v -1] = 1;
    }
    liberar_fila(&fila);
}

int eh_bipartido(GrafoLista* grafo){
    if(!grafo) return -1;
    int visitado[grafo->capacidade];
    int distancia[grafo->capacidade];
    int predecessor[grafo->capacidade];
    int cor[grafo->capacidade];
    
    for(int i = 0; i < grafo->capacidade; i++){
        for(int k = 0; k < grafo->capacidade; k++){visitado[k] = 0; distancia[k] = 0; predecessor[k] = 0; cor[k] = 0;}

        bfs(grafo,i + 1,visitado,distancia,predecessor);
        for(int j = 0; j < grafo->capacidade; j++){
            if(distancia[j] == 0)continue;
            else if(distancia[j] % 2 == 0)cor[j] = 1;
            else cor[j] = 2;
        }

        for(int j = 0; j < grafo->capacidade; j++){
            if(cor[j] == 0){
                continue;
            }else if(i == j){
                continue;
            }else if(cor[j] == cor[predecessor[j] - 1])return 0;
        }
    }
    
    return 1;
}

int tem_circulo(GrafoLista* grafo){
    if(!grafo) return -1;
    int visitado[grafo->capacidade];
    for(int i = 0; i < grafo->capacidade; i++){
        for(int j = 0; j < grafo->capacidade; j++)visitado[j] = 0;
        if(dfs_verificacao_circulo(grafo, i + 1, visitado) == 1) return 1;
    }
    return 0;
}


int contar_componentes(GrafoLista* grafo){
    if(!grafo) return -1;
    if(grafo->eh_orientado){printf("Essa contagem de componentes serve apenas para grafos não orientados"); return -1;}
    
    int qtd_componentes = 0;
    int* visitado = (int*)calloc(grafo->capacidade, sizeof(int));

    for(int i = 0; i < grafo->capacidade; i++){
        if(!visitado[i]){
            qtd_componentes++;
            dfs_simples(grafo,i+1,visitado);
        }
    }

    free(visitado);
    return qtd_componentes;
}


// ---------------------------------------- funções pratica 04 ----------------------------------------


int dfs_articulacoes(GrafoLista* grafo, int** componetes, int *low){
    if(!grafo) return -1;
    if(grafo->eh_orientado == 0) return -1;
    Pilha* pilha = criar_pilha();
    
    int *descoberto = calloc(grafo->capacidade, sizeof(int));
    int idx_compontente = 0;
    int idx_visto = 0;
    for(int i = 0 ; i < grafo->capacidade; i++){
        descoberto[i] = -1;
        low[i] = -1;
    }


    for(int i = 0 ; i < grafo->capacidade; i++){
        if(descoberto[i] != -1 ) continue;
        dfs_tarjan(grafo, i+1, pilha,componetes, descoberto, low, &idx_compontente, &idx_visto);
    }
    
    free(descoberto);
    liberar_pilha(&pilha);
    return idx_compontente;
}


No** detectar_pontes(GrafoLista* grafo){
    if(!grafo) return NULL;

    int n = grafo->capacidade;
    int* visitado = (int*)calloc(n, sizeof(int));
    int* descoberto = (int*)calloc(n, sizeof(int));
    int* low_arr = (int*)calloc(n, sizeof(int));

    // aloca espaço máximo para pontes (no máximo n-1 pontes)
    No** pontes = (No**)calloc(n, sizeof(No*));
    int idx_ponte = 0;
    int timer = 0;

    for(int i = 0; i < n; i++){
        if(!visitado[i]){
            dfs_pontes(grafo, i + 1, -1, visitado, descoberto, low_arr, &timer, pontes, &idx_ponte);
        }
    }

    free(visitado);
    free(descoberto);
    free(low_arr);

    return pontes;
}

int eh_planar_euler(GrafoLista *grafo){
    if(!grafo) return -1;

    int n = grafo->capacidade;
    int m = contar_arestas(grafo);

    // Condição necessária pela fórmula de Euler: m <= 3n - 6 (para n >= 3)
    // Se falhar, o grafo definitivamente NÃO é planar
    if(n >= 3 && m > 3 * n - 6) return 0;

    // Para n <= 10: teste de subdivisões de K5 e K3,3 (força bruta)
    // Pelo Teorema de Kuratowski: um grafo é planar sse não contém
    // subdivisão de K5 nem de K3,3
    if(n <= 10){
        if(tem_subdivisao_k5(grafo)) return 0;
        if(tem_subdivisao_k33(grafo)) return 0;
    }

    // Passou em todos os testes: considerado planar
    return 1;
}



// ---------------------------------------- funções auxiliares ----------------------------------------


void dfs_simples(GrafoLista* grafo, int u, int* visitado){
    if(!grafo || !visitado)return;
    visitado[u - 1] = 1;
    No* aux = grafo->lista[u - 1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            dfs_verificacao_circulo(grafo, aux->vertice, visitado);
        }
        aux = aux->prox;
    }
}

int dfs_verificacao_circulo(GrafoLista* grafo, int u, int* visitado){
    if(!grafo || !visitado)return -1;
    visitado[u - 1] = 1;
    No* aux = grafo->lista[u - 1];
    while(aux){
        if(!visitado[aux->vertice - 1]){
            dfs_verificacao_circulo(grafo, aux->vertice, visitado);
        }else{
            return 1;
        }
        aux = aux->prox;
    }
    return 0;
}

void dfs_tarjan(GrafoLista* grafo, int u, Pilha* pilha, int **componentes, int* descoberto, int *low, int* idx_componetes, int *idx_visto){
    if(!grafo)return;
    descoberto[u-1] = low[u -1] =  ++(*idx_visto);
    push(pilha, u);
    No* aux = grafo->lista[u-1];
    while(aux){
        int v = aux->vertice;
        if(descoberto[v -1] == -1){
            dfs_tarjan(grafo,v,pilha,componentes,descoberto,low,idx_componetes, idx_visto);
            low[u -1] = min(low[u-1],low[v-1]);
        }else if(LIFO_search_value(pilha,v)){
            low[u -1] = min(low[u -1],descoberto[v -1]);
        }
        aux = aux->prox;
    }
    

    if(low[u -1] == descoberto[u-1]){
        int v = -1;
        int i = 0;
        while(v != u){
            v = pop(pilha);
            componentes[*idx_componetes][i] = v;
            i++;
        }
        (*idx_componetes)++;
    }
}



int min(int number1, int number2){
    if(number1 < number2) return number1;
    return number2;
}

void dfs_pontes(GrafoLista* grafo, int u, int pai, int* visitado, int* descoberto, int* low, int* timer, No** pontes, int* idx_ponte){
    if(!grafo) return;
    visitado[u - 1] = 1;
    descoberto[u - 1] = low[u - 1] = ++(*timer);

    No* aux = grafo->lista[u - 1];
    while(aux){
        int v = aux->vertice;
        if(!visitado[v - 1]){
            dfs_pontes(grafo, v, u, visitado, descoberto, low, timer, pontes, idx_ponte);
            low[u - 1] = min(low[u - 1], low[v - 1]);

            // se low[v] > descoberto[u], a aresta (u, v) é ponte
            if(low[v - 1] > descoberto[u - 1]){
                No* no_u = (No*)malloc(sizeof(No));
                No* no_v = (No*)malloc(sizeof(No));
                no_u->vertice = u;
                no_u->prox = no_v;
                no_v->vertice = v;
                no_v->prox = NULL;
                pontes[*idx_ponte] = no_u;
                (*idx_ponte)++;
            }
        } else if(v != pai){
            low[u - 1] = min(low[u - 1], descoberto[v - 1]);
        }
        aux = aux->prox;
    }
}

int contar_arestas(GrafoLista* grafo){
    if(!grafo) return 0;
    int total = 0;
    for(int i = 0; i < grafo->capacidade; i++){
        No* aux = grafo->lista[i];
        while(aux){
            total++;
            aux = aux->prox;
        }
    }
    if(!grafo->eh_orientado) total /= 2;
    return total;
}


int dfs_caminho(GrafoLista* grafo, int atual, int destino, int* usado, int* no_caminho, int* branch, int num_branch, int pares[][2], int num_pares, int par_atual){
    if(atual == destino){
        for(int i = 0; i < grafo->capacidade; i++){
            if(no_caminho[i]) usado[i] = 1;
        }
        int resultado = tentar_caminhos_disjuntos(grafo, pares, num_pares, par_atual + 1, usado, branch, num_branch);
        if(resultado) return 1;
        for(int i = 0; i < grafo->capacidade; i++){
            if(no_caminho[i]) usado[i] = 0;
        }
        return 0;
    }

    No* aux = grafo->lista[atual - 1];
    while(aux){
        int v = aux->vertice;
        if(!usado[v - 1] && !no_caminho[v - 1]){
            int pular = 0;
            if(v != destino){
                for(int i = 0; i < num_branch; i++){
                    if(branch[i] == v){ pular = 1; break; }
                }
            }
            if(!pular){
                if(v != destino) no_caminho[v - 1] = 1;
                if(dfs_caminho(grafo, v, destino, usado, no_caminho, branch, num_branch, pares, num_pares, par_atual)){
                    return 1;
                }
                if(v != destino) no_caminho[v - 1] = 0;
            }
        }
        aux = aux->prox;
    }
    return 0;
}

int tentar_caminhos_disjuntos(GrafoLista* grafo, int pares[][2], int num_pares, int par_atual, int* usado, int* branch, int num_branch){
    if(par_atual >= num_pares) return 1;

    int* no_caminho = (int*)calloc(grafo->capacidade, sizeof(int));
    int resultado = dfs_caminho(grafo, pares[par_atual][0], pares[par_atual][1], usado, no_caminho, branch, num_branch, pares, num_pares, par_atual);
    free(no_caminho);
    return resultado;
}


int tem_subdivisao_k5(GrafoLista* grafo){
    int n = grafo->capacidade;
    if(n < 5) return 0;

    int branch[5];
    for(branch[0] = 1; branch[0] <= n - 4; branch[0]++){
        for(branch[1] = branch[0] + 1; branch[1] <= n - 3; branch[1]++){
            for(branch[2] = branch[1] + 1; branch[2] <= n - 2; branch[2]++){
                for(branch[3] = branch[2] + 1; branch[3] <= n - 1; branch[3]++){
                    for(branch[4] = branch[3] + 1; branch[4] <= n; branch[4]++){
                        // gera os C(5,2) = 10 pares
                        int pares[10][2];
                        int idx = 0;
                        for(int i = 0; i < 5; i++){
                            for(int j = i + 1; j < 5; j++){
                                pares[idx][0] = branch[i];
                                pares[idx][1] = branch[j];
                                idx++;
                            }
                        }
                        int* usado = (int*)calloc(n, sizeof(int));
                        if(tentar_caminhos_disjuntos(grafo, pares, 10, 0, usado, branch, 5)){
                            free(usado);
                            return 1;
                        }
                        free(usado);
                    }
                }
            }
        }
    }
    return 0;
}

int tem_subdivisao_k33(GrafoLista* grafo){
    int n = grafo->capacidade;
    if(n < 6) return 0;

    int vertices[6];
    for(vertices[0] = 1; vertices[0] <= n - 5; vertices[0]++){
        for(vertices[1] = vertices[0] + 1; vertices[1] <= n - 4; vertices[1]++){
            for(vertices[2] = vertices[1] + 1; vertices[2] <= n - 3; vertices[2]++){
                for(vertices[3] = vertices[2] + 1; vertices[3] <= n - 2; vertices[3]++){
                    for(vertices[4] = vertices[3] + 1; vertices[4] <= n - 1; vertices[4]++){
                        for(vertices[5] = vertices[4] + 1; vertices[5] <= n; vertices[5]++){
  
                            for(int i = 1; i < 6; i++){
                                for(int j = i + 1; j < 6; j++){
                                    int a[3] = {vertices[0], vertices[i], vertices[j]};
                                    int b[3];
                                    int bi = 0;
                                    for(int k = 1; k < 6; k++){
                                        if(k != i && k != j) b[bi++] = vertices[k];
                                    }

                                    int pares[9][2];
                                    int idx = 0;
                                    for(int ai = 0; ai < 3; ai++){
                                        for(int bj = 0; bj < 3; bj++){
                                            pares[idx][0] = a[ai];
                                            pares[idx][1] = b[bj];
                                            idx++;
                                        }
                                    }

                                    int branch[6];
                                    for(int k = 0; k < 6; k++) branch[k] = vertices[k];

                                    int* usado = (int*)calloc(n, sizeof(int));
                                    if(tentar_caminhos_disjuntos(grafo, pares, 9, 0, usado, branch, 6)){
                                        free(usado);
                                        return 1;
                                    }
                                    free(usado);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}