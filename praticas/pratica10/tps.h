#ifndef TPS_H
#define TPS_H

#include "hamiltoniano.h"

// tsp_forca_bruta(...) — fixa origem, gera ( n − 1 ) ! permutações.
// Preenche 'melhor_rota' com n + 1 vértices (incluindo retorno à origem) e retorna o custo mínimo (-1 se inviável).
int tsp_forca_bruta(GrafoListaPonderado *g, int origem, int *melhor_rota);

// tsp_vizinho_mais_proximo(...) — heurística construtiva.
// Preenche 'rota' com n + 1 vértices (incluindo retorno à origem) e retorna o custo total (-1 se inviável).
int tsp_vizinho_mais_proximo(GrafoListaPonderado *g, int origem, int *rota);

// tsp_insercao(...) — heurística de inserção do mais próximo.
// Preenche 'rota' com n + 1 vértices (incluindo retorno à origem) e retorna o custo total (-1 se inviável).
int tsp_insercao(GrafoListaPonderado *g, int origem, int *rota);

#endif
