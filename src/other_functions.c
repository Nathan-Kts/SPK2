#include "other_functions.h"

void duplicate_matrix(int m, int n, double input[m][n], double output[m][n]){
    int i, j;
    for(i=0; i<m; i++){
        for(j=0; j<n; j++){
            output[i][j]=input[i][j];
        }
    }
}