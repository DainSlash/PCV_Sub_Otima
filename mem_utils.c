#include "mem_utils.h"

int** create_matrix(int N){
    int ** matrix = (int **) malloc(sizeof(int*) * N);
    int i, j;
    for (i = 0; i < N; i++) {
        matrix[i] = (int *) malloc(sizeof(int) * N);
        for(j = 0; j < N ; j++) matrix[i][j] = INT_MAX;
    }
    return matrix;
}   

void free_matrix(int** matrix, int N){
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int* create_vector(int N){
    return (int *) calloc(sizeof(int), N);
}

float get_media_extremos(int **matrix, int N){
    int i, j;
    int maior = 0, menor = INT_MAX;
    for (i = 0; i < N ; i++) for (j = 0; j < N; j++) if (i!=j){
        maior = (matrix[i][j] > maior) ? matrix[i][j] : maior; 
        menor = (matrix[i][j] < menor) ? matrix[i][j] : menor;
    }

    return (maior + menor)/2.0;
}

float get_media_arestas(int **matrix, int N){
    int i, j;
    float total = 0;
    float qtd_arestas = 0;
    for (i = 0; i < N; i++) for (j = 0; j < N; j++) if(i!=j){
        total+= matrix[i][j];
        qtd_arestas++;
    } 

    return (N > 0) ? total/qtd_arestas : 0;
}


Solucao init_solucao(int **matrix, int N){
    Solucao solucao;
    solucao.caminho = create_vector(N);
    solucao.custos_caminhos = create_vector(N);
    solucao.custo_atual = 0;
    solucao.menor_custo = INT_MAX;
    solucao.qtd_arestas = N;
    solucao.media_das_arestas = get_media_arestas(matrix, N);
    solucao.media_dos_extremos = get_media_extremos(matrix, N);
    solucao.media_do_caminho = 0;
    return solucao;
}