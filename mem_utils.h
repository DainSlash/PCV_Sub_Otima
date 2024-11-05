#ifndef MEMUTILS_H
#define MEMUTILS_H

#include <limits.h>
#include <stdlib.h>

typedef struct {
    int *caminho;
    int *custos_caminhos;
    int custo_atual;
    int qtd_arestas;
    float media_dos_extremos;
    float media_das_arestas;
    float media_do_caminho;
} Solucao;

int** create_matrix(int N, int M);
void free_matrix(int** matrix, int N);
int* create_vector(int N);
Solucao init_solucao(int **matrix, int N);
float get_media_extremos(int **matrix, int N);
float get_media_arestas(int **matrix, int N);

#endif