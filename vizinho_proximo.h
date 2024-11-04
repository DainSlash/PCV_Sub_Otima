#ifndef VIZINHOPROXIMO_H
#define VIZINHOPROXIMO_H

#include <limits.h>
#include <stdlib.h>
#include "mem_utils.h"

int obter_prox_vertice(int* visitados, int** matrix, int N, int vertice_atual);
void fechar_ciclo(Solucao *result, int inicio, int** matrix, int vertice_atual, int num_visitados);
void atualizar_caminho(Solucao *result, int proximo, int custo, int* visitados, int* num_visitados, int* vertice_atual);
Solucao vizinho_proximo(int ** matrix, int N, int inicio);

#endif