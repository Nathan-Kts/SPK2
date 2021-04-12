//
// Created by Nathan on 15/03/2021.
//

#include "quality.h"

double max_norm(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size]){
    double max_length = 0;
    double temp = 0;
    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            temp += input[i][j]*input[i][j];
        }
        if(temp > max_length)
            max_length = temp;
        temp = 0.0;
    }
    return sqrt(max_length);
}

double total_norm(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size]){
    double total_length = 0;
    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            total_length += input[i][j]*input[i][j];
        }
    }
    return sqrt(total_length);
}

double gram_schimdt_norm(int nbr_vectors, int vector_size, double A[nbr_vectors][vector_size], double Q[nbr_vectors][vector_size]) {
    int i, j, k;
    double A0[nbr_vectors][vector_size];
    double temp;

    for (i = 0; i < nbr_vectors; i++){
        for (j = 0; j < vector_size; j++) {
            A0[i][j] = A[i][j];
        }
    }

    for(i=0; i<VECTOR_SIZE; ++i) {
        // Normalisation ok column i
        double scaling_factor = 0;
        for(j=0; j<VECTOR_SIZE; ++j)
            scaling_factor += A0[j][i]*A0[j][i];
        scaling_factor = sqrt(scaling_factor);
        for(j=0; j<VECTOR_SIZE; ++j)
            Q[j][i] = A0[j][i]/scaling_factor;

        //Orthogonalization of all the other columns
        for(k=i+1; k<VECTOR_SIZE; k++){
            temp = product_vector_vector(nbr_vectors, vector_size, A0, k, Q, i, nbr_vectors);
            //printf("%d\n", (int) (1000*temp));
            for(j=0; j<VECTOR_SIZE; j++){
                A0[j][k] = A0[j][k] - Q[j][i]*temp;
            }
        }
    }
    product_matrix_prime_matrix(nbr_vectors, vector_size, Q, A, A0);
    for (i = 0; i < VECTOR_SIZE; i++){
        for (j = 0; j < VECTOR_SIZE; j++) {
            Q[i][j] = A0[i][j];
        }
    }
    return max_norm(nbr_vectors, vector_size, Q);
}
