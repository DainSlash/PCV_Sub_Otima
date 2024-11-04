#ifndef INFOUTILS_H
#define INFOUTILS_H
#define static_size 7

#include <stdio.h>
#include "mem_utils.h"

void print_matrix(int** matrix, int N);
void get_infos_by_scanf(int *** matrix, int *N, int *inicio);
void get_infos_static(int *** matrix, int *N, int *inicio);
void print_solucao(Solucao solucao, int N);


#endif