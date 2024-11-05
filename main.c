#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <string.h>
#include "mem_utils.h"
#include "vizinho_proximo.h"
#include "info_utils.h"


bool solucao_boa(Solucao solucao){
    int abs_dif = ((int)(solucao.media_das_arestas-solucao.media_dos_extremos)>0 ? (int)(solucao.media_das_arestas-solucao.media_dos_extremos) : (int)(solucao.media_das_arestas-solucao.media_dos_extremos)*-1);
   // return ((int)(solucao.media_do_caminho*abs_dif) <= (int)(solucao.media_das_arestas)); Não consegui chegar em uma formula ainda.
   return false;
}

int get_max_iteracoes(Solucao solucao){
    int abs_dif = ((int)solucao.media_do_caminho-(int)solucao.media_das_arestas) > 0 ? (int)solucao.media_do_caminho-(int)solucao.media_das_arestas: ((int)solucao.media_do_caminho-(int)solucao.media_das_arestas)*-1;
    return (int)((solucao.qtd_arestas)*abs_dif);
}


int avaliar_solucao(int *permutacao, int **matrix, int N){
    int tam = 0, i;
    for (i = 0; i < N - 1; i++) {
        int u = permutacao[i];
        int v = permutacao[i + 1];
        tam += matrix[u][v]; 
    }
    return tam;
}

void trocar_posicoes(int *permutacao, int i, int j) {
    int temp = permutacao[i];
    permutacao[i] = permutacao[j];
    permutacao[j] = temp;
}

bool banido(int **movimentos_banidos, int iteracao, int i, int j) {
    int k;
    for (k = 0; k < iteracao; k++) {
        if ((movimentos_banidos[k][0] == i && movimentos_banidos[k][1] == j) ||
            (movimentos_banidos[k][0] == j && movimentos_banidos[k][1] == i)) {
            return true;
        }
    }
    return false;
}

int* get_custos_caminhos(Solucao solucao, int **matrix, int N) {
    int *result = create_vector(N + 1);
    int i;

    result[0] = 0;
    for (i = 1; i < N; i++) {
        int u = solucao.caminho[i - 1];
        int v = solucao.caminho[i];
        result[i] = matrix[u][v];
    }
    result[N] = matrix[solucao.caminho[N - 1]][solucao.caminho[0]];
    return result;
}

Solucao busca_tabu(Solucao solucao, int **matrix, int N) {
    int iteracao = 0, MAX_I = get_max_iteracoes(solucao);
    int *permutacao_atual = create_vector(N);
    int **movimentos_banidos = create_matrix(MAX_I, 2);
    int i, j;
    memcpy(permutacao_atual, solucao.caminho, N * sizeof(int));

    while (iteracao < MAX_I) {
        int melhor_custo = INT_MAX;
        int *melhor_vizinho = NULL;

        for (i = 0; i < N; i++) {
            for (j = i + 1; j < N; j++) {
                if (banido(movimentos_banidos, iteracao, i, j)) continue;

                int *vizinho = create_vector(N);
                memcpy(vizinho, permutacao_atual, N * sizeof(int));

                trocar_posicoes(vizinho, i, j);

                int custo_vizinho = avaliar_solucao(vizinho, matrix, N);
                if (custo_vizinho < melhor_custo) {
                    melhor_custo = custo_vizinho;
                    if (melhor_vizinho) {
                        free(melhor_vizinho);
                    }
                    melhor_vizinho = vizinho;
                } else {
                    free(vizinho);
                }
            }
        }

        if (melhor_vizinho) {
            memcpy(solucao.caminho, melhor_vizinho, N * sizeof(int));
            solucao.custo_atual = melhor_custo;

            movimentos_banidos[iteracao][0] = i;
            movimentos_banidos[iteracao][1] = j;
            iteracao++;

            free(melhor_vizinho);
        } else {
            break; 
        }
    }

    solucao.custos_caminhos = get_custos_caminhos(solucao, matrix, N);
    solucao.custo_atual = 0;
    for (i = 0; i <= N; i++) {
        solucao.custo_atual += solucao.custos_caminhos[i];
    }
    solucao.media_do_caminho = solucao.custo_atual / (float)(N + 1);

    free_matrix(movimentos_banidos, MAX_I);
    free(permutacao_atual);
    return solucao;
}


int main(){
    int N, inicio;
    int** matrix;

    //get_infos_by_scanf(&matrix, &N, &inicio);
    get_infos_static(&matrix, &N, &inicio);

    print_matrix(matrix, N);
    Solucao solucao = vizinho_proximo(matrix, inicio, N);
    print_solucao(solucao, N);
    if (!solucao_boa(solucao)) solucao = busca_tabu(solucao, matrix, N);
    print_solucao(solucao, N);

    //liberar a memoria alocada
    free(solucao.caminho);
    free(solucao.custos_caminhos);
    free_matrix(matrix, N);
    return 0;
}