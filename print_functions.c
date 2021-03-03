//
// Created by Nathan on 03/03/2021.
//

#include "print_functions.h"

void print_matrix(int m, int n, double matrix[m][n]){
    int i,j;
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            printf("%10.4f\t", matrix[i][j]);
        }
        printf("\n");
    }
}