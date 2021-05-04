//
// Created by Nathan on 03/03/2021.
//
#include "print_functions.h"

void print_matrix(int n, int m, double matrix[n][m]){
    int i,j;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++)
            printf("%20.6f", matrix[i][j]);
        printf("\n");
    }
}

void print_vector(int n, double vector[n]){
    int i;
    for(i=0; i<n; i++)
            printf("%20.2f", vector[i]);
    printf("\n");
}