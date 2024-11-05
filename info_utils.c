#include "info_utils.h"

void print_matrix(int** matrix, int N){
    int i, j;
    for (i = 0; i < N ; i++) {
        printf("\n");   
        for (j = 0; j < N ; j++) if(matrix[i][j] == INT_MAX) printf(" -1 "); else printf(" %d ", matrix[i][j]);
    }
    printf("\n");   
}

void print_solucao(Solucao solucao, int N) {
    int i;
    printf("\n\nCaminho: ");
    for (i = 0; i < N+1; i++) printf("%c ", 'A' + solucao.caminho[i]);
    printf("\nCustos: ");
    for (i = 0; i < N+1; i++) printf("%d ",  solucao.custos_caminhos[i]);
    printf("\nCusto Total: %d", solucao.custo_atual);
    printf("\nQuantidade de Arestas: %d", solucao.qtd_arestas);
    printf("\nMedia dos Extremos: %.2f", solucao.media_dos_extremos);
    printf("\nMedia das Arestas: %.2f\n", solucao.media_das_arestas);
    printf("\nMedia do Caminho: %.2f\n", solucao.media_do_caminho);
}


//metodo usado para criar dinamicamente o grafo.
void get_infos_by_scanf(int *** matrix, int *N, int *inicio){
    int i, j;
    
    printf("Informe a quantidade de vertices: ");
    scanf("%d",N);
    *matrix = create_matrix(*N, *N);


    printf("\nAgora digite a distancia entre o respectivo vertice para cada um dos subsequentes(-1 equivale a inexistencia do caminho)\n");
    for (i = 0 ; i < *N ; i++) {
        for (j = 0 ; j < *N ; j++){
            if (i!=j){
                printf("\t%c", 'A' + j);
                if (j < (*N-1) && !(j == (*N-2) && i == (*N-1))) printf("\t-->");
            }
        }
        printf("\n%c: ", 'A' + i);
        for (j = 0; j < *N ; j++) {
            if (i!=j){
                scanf("%d", &(*matrix)[i][j]);
            }

        }
    }


    printf("\nAgora selecione o vertice de inicio (de: 0 A: N): \n");
    scanf("%d",inicio);

    while (inicio > N) {
        printf("\nSelecione um inicio valido: \n");
        scanf("%d",inicio);
    }
}


//metodo para pegar estaticamente, para facilitar o desenvolivmento e testes.
void get_infos_static(int *** matrix, int *N, int *inicio){
    *N = static_size;
    *inicio = 0;

    int valores[static_size][static_size] = {
        { INT_MAX, 10, 40, 20, 100, 50, 80 },
        { 10, INT_MAX, 30, 60, 15, 90, 25 },
        { 40, 30, INT_MAX, 5, 20, 30, 70 },
        { 20, 60, 5, INT_MAX, 10, 15, 50 },
        { 100, 15, 20, 10, INT_MAX, 5, 35 },
        { 50, 90, 30, 15, 5, INT_MAX, 10 },
        { 80, 25, 70, 50, 35, 10, INT_MAX }
    };


    (*matrix) = create_matrix(*N, *N);
    int i, j;
    for (i = 0; i < *N; i ++) for (j = 0 ; j < *N ; j++) (*matrix)[i][j] = valores[i][j];

}
