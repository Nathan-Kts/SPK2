#include "lattice_functions.h"

/**
 * @brief Creates a random lattice
 * @param n
 * @param m
 * @param output
 */
void create_random_lattice(int n, int m, double output[n][m]){
    int i, j;

    for (i = 0; i<n; i++)
        for (j = 0; j < m; j++)
            output[i][j] = rand()%MODULO_LATTICE;
}//end create_lattice()

void public_generation(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]){
    int i, j, k, multiplier;
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            public_lattice[i][j] = 0;
    for(i = 0; i < nbr_vectors; i++){
        for(j = i; j < nbr_vectors; j++) {
            multiplier = (rand() % 5)+1;
            for(k = 0; k < vector_size; k++) {
                public_lattice[i][k] += multiplier * private_lattice[j][k];
                //printf("%10.4f %d %10.4f %d %d %d\n", public_lattice[i][k], multiplier, private_lattice[j][k], i, j, k);
            }
        }
        for(k = 0; k < vector_size; k++)
            public_lattice[i][k] = modd(public_lattice[i][k]+1, MODULO_LATTICE);
    }
}

/**
 * @brief
 * @param message
 */
void decoding(int vector_size, double message[vector_size]){
    int i;
    for(i = 0; i < vector_size; i++) {
        if (message[i]<16 || message[i]>=48)
            message[i] = 1;
        else
            message[i] = 0;
    }
}

/**
 * @brief
 * @param message
 */
void noise_maker(int vector_size, double message[vector_size]){
    int i;
    for(i = 0; i < vector_size; i++) {
        message[i] += (rand() % 3) - 1;
        message[i] = modd(message[i]+0.5, MODULO_LATTICE);
    }

}