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

double norm(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size]){
    double max_length = 0;
    double min_length = 10000000000000;
    double temp = 0;
    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            temp += input[i][j]*input[i][j];
        }
        if(temp > max_length)
            max_length = temp;
        if(temp < min_length)
            min_length = temp;
        temp = 0.0;
    }
    return sqrt(min_length)/sqrt(max_length);
}

double vec_norm(int nbr_vectors, int vector_size, int line, double input[nbr_vectors][vector_size]){
    double temp = 0;
    for (int i = 0; i < nbr_vectors; ++i) {
        temp += input[line][i]*input[line][i];
    }
    return sqrt(temp);
}

/*double total_norm(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size]){
    double total_length = 0;
    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            total_length += input[i][j]*input[i][j];
        }
    }
    return sqrt(total_length);
}*/

double gs_norm(int nbr_vectors, int vector_size, double A[nbr_vectors][vector_size], double Q[nbr_vectors][vector_size]) {
    int i, j, k;
    double A0[nbr_vectors][vector_size];
    double temp;

    // Copy of vector and initialisation of output
    for (i = 0; i < nbr_vectors; i++){
        for (j = 0; j < vector_size; j++) {
            A0[i][j] = A[i][j];
            Q[i][j] = 0;
        }
    }

    for(i=0; i<vector_size; ++i) {
        // Normalisation ok column i
        double scaling_factor = 0;
        for(j=0; j<vector_size; ++j)
            scaling_factor += A0[j][i]*A0[j][i];
        scaling_factor = sqrt(scaling_factor);
        for(j=0; j<vector_size; ++j)
            Q[j][i] = A0[j][i]/scaling_factor;

        //Orthogonalization of all the other columns
        for(k=i+1; k<vector_size; k++){
            temp = product_vector_vector(nbr_vectors, vector_size, A0, k, Q, i, nbr_vectors);
            //printf("%d\n", (int) (1000*temp));
            for(j=0; j<vector_size; j++){
                A0[j][k] = A0[j][k] - Q[j][i]*temp;
            }
        }
    }
    product_matrix_prime_matrix(nbr_vectors, vector_size, Q, A, A0);
    for (i = 0; i < vector_size; i++){
        for (j = 0; j < vector_size; j++) {
            Q[i][j] = A0[i][j];
        }
    }
    return norm(nbr_vectors, vector_size, Q);
}


double hamdamard_ratio(int nbr_vectors, double input[nbr_vectors][nbr_vectors]){
    double temp[nbr_vectors][nbr_vectors];
    for (int i = 0; i < nbr_vectors; i++){
        for (int j = 0; j < nbr_vectors; j++) {
            temp[i][j] = input[i][j];
        }
    }
    gauss_elimination(nbr_vectors, nbr_vectors, temp);
    double detOfLattice = 1;
    for(int i = 0; i < nbr_vectors; i++) {
        detOfLattice *= temp[i][i];
    }
    float mult = 1;
    for (int i = 0; i < nbr_vectors; i++) {
        mult = mult * vec_norm(nbr_vectors, nbr_vectors, i, input);
    }
    double hratio = powf((detOfLattice / mult),(1.0 / nbr_vectors));
    return hratio;
}