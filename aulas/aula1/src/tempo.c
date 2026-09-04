#include <time.h>
#include "../include/tempo.h"


clock_t inicio;
clock_t fim;

void inicia_clock(){
  inicio = clock();
}

void finaliza_clock(){
  fim = clock();
}

double tempo_execucao(){
  return (double) (fim - inicio)/CLOCKS_PER_SEC;
}
