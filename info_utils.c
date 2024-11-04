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
    printf("\n\nCaminho: ");
    for (int i = 0; i < N+1; i++) printf("%c ", 'A' + solucao.caminho[i]);
    printf("\nCustos: ");
    for (int i = 0; i < N+1; i++) printf("%d ",  solucao.custos_caminhos[i]);
    printf("\nCusto Total: %d", solucao.custo_atual);
    printf("\nMenor Custo: %d", solucao.menor_custo);
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
    *matrix = create_matrix(*N);


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
        { INT_MAX, 10, 15, 20, 25, 30, 35 },
        { 10, INT_MAX, 12, 18, 22, 27, 30 },
        { 15, 12, INT_MAX, 14, 20, 24, 28 },
        { 20, 18, 14, INT_MAX, 16, 20, 25 },
        { 25, 22, 20, 16, INT_MAX, 15, 18 },
        { 30, 27, 24, 20, 15, INT_MAX, 14 },
        { 35, 30, 28, 25, 18, 14, INT_MAX }
    };

    (*matrix) = create_matrix(*N);
    int i, j;
    for (i = 0; i < *N; i ++) for (j = 0 ; j < *N ; j++) (*matrix)[i][j] = valores[i][j];

}
