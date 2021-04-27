#include "crypto_functions.h"
#include "math_functions.h"
#include "print_functions.h"

void decode(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]){
    product_matrix_vector(nbr_vectors, vector_size, private_lattice, message, decode);

    printf("Message decoded by 1 : \n");
    for (int i = 0; i < vector_size; ++i) {
        decode[i] = modd(decode[i], MODULO_LATTICE);
    }
    print_vector(vector_size, decode);

    decoding(vector_size, decode);
    print_vector(vector_size, decode);
}

void nearest_plane(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]){
    double gs[NBR_VECTORS][VECTOR_SIZE];
    for(int i = 0; i < nbr_vectors; i++)
        for(int j = 0; j < vector_size; j++)
            gs[i][j] = private_lattice[i][j];

    gram_schimdt(nbr_vectors, gs);
    double w[NBR_VECTORS][VECTOR_SIZE];
    double y[NBR_VECTORS][VECTOR_SIZE];
    double l;
    for (int i = 0; i < nbr_vectors; ++i) {
        w[nbr_vectors-1][i] = message[i];
    }
    for (int i = nbr_vectors-1; i > 0; i--) {
        l = product_vector_vector(nbr_vectors, vector_size, w, i, gs, i, nbr_vectors)/product_vector_vector(nbr_vectors, vector_size, gs, i, gs, i, nbr_vectors);
        for (int j = 0; j < nbr_vectors; ++j) {
            y[i][j] = (double) (int) l * private_lattice[i][j];
        }
        for (int j = 0; j < nbr_vectors; ++j) {
            w[i-1][j] = w[i][j] - (l - (double) (int) l)*gs[i][j] - ((double) (int) l)*private_lattice[i][j];
        }
    }

    for(int i = 0; i < nbr_vectors; i++)
        for(int j = 0; j < vector_size; j++)
            decode[i] = y[i][j];

    printf("Message decoded by 1 : \n");
    print_vector(vector_size, decode);
}

/**
 * @brief
 * @param message
 */
void decoding(int vector_size, double message[vector_size]){
    int i;
    for(i = 0; i < vector_size; i++) {
        if (message[i]<(MODULO_LATTICE/4) || message[i]>=(3*MODULO_LATTICE/4))
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
    double temp;
    for(i = 0; i < vector_size; i++) {
        temp = (rand() % 4) - 2;
        //printf("%f\n", temp);
        message[i] += temp;
        //message[i] = modd(message[i]+0.5, MODULO_LATTICE);
    }

}