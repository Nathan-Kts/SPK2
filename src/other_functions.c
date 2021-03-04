#include "other_functions.h"

void duplicate_matrix(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]){
    int i, j;
    for(i=0; i < nbr_vectors; i++){
        for(j=0; j < vector_size; j++){
            output[i][j]=input[i][j];
        }
    }
}