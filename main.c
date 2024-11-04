#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "mem_utils.h"
#include "vizinho_proximo.h"
#include "info_utils.h"


bool solucao_boa(Solucao solucao){
    return (solucao.media_do_caminho <= solucao.media_das_arestas);
}

void busca_tabu(){
    // falta implementar
}


int main(){
    int N, inicio;
    int** matrix;

    //get_infos_by_scanf(&matrix, &N, &inicio);
    get_infos_static(&matrix, &N, &inicio);

    print_matrix(matrix, N);
    Solucao solucao = vizinho_proximo(matrix, N, inicio);
    print_solucao(solucao, N);
    if (!solucao_boa(solucao)) busca_tabu();

    //liberar a memoria alocada
    free(solucao.caminho);
    free(solucao.custos_caminhos);
    free_matrix(matrix, N);
    return 0;
}