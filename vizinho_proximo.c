#include "vizinho_proximo.h"

int obter_prox_vertice(int* visitados, int** matrix, int N, int vertice_atual) {
    int menor = INT_MAX, proximo = -1;
    for (int j = 0; j < N; j++) {
        if (!visitados[j] && matrix[vertice_atual][j] < menor) {
            menor = matrix[vertice_atual][j];
            proximo = j;
        }
    }
    return proximo;
}

void fechar_ciclo(Solucao *result, int inicio, int** matrix, int vertice_atual, int num_visitados) {
    result->caminho[num_visitados] = inicio;
    result->custos_caminhos[num_visitados] = matrix[vertice_atual][inicio];
    result->custo_atual += matrix[vertice_atual][inicio];
}

void atualizar_caminho(Solucao *result, int proximo, int custo, int* visitados, int* num_visitados, int* vertice_atual) {
    visitados[proximo] = 1;
    result->custos_caminhos[*num_visitados] = custo;
    result->caminho[(*num_visitados)++] = proximo;
    result->custo_atual += custo;
    *vertice_atual = proximo;
}

Solucao vizinho_proximo(int ** matrix, int N, int inicio){
    Solucao result = init_solucao(matrix, N);
    int *visitados = create_vector(N);
    
    int i, j;
    int vertice_atual = inicio;
    int num_visitados = 0;

    visitados[vertice_atual] = 1;
    result.caminho[num_visitados++] = vertice_atual;

  while (num_visitados < N) {
        int proximo = obter_prox_vertice(visitados, matrix, N, vertice_atual);
        if (proximo != -1) {
            atualizar_caminho(&result, proximo, matrix[vertice_atual][proximo], visitados, &num_visitados, &vertice_atual);
        }
    }

    fechar_ciclo(&result, inicio, matrix, vertice_atual, num_visitados);
    result.media_do_caminho = result.custo_atual/(float)num_visitados;

    free(visitados);
    result.menor_custo = result.custo_atual;
    return result;
}