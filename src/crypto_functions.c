#include "crypto_functions.h"
#include "math_functions.h"
#include "print_functions.h"

void decode(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]){
    product_matrix_vector(nbr_vectors, vector_size, private_lattice, message, decode);
    //printf("Message decoded by 1 : \n");
    //print_vector(vector_size, decode);
    decoding(vector_size, decode);
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
    for(i = 0; i < vector_size; i++) {
        message[i] += (rand() % 100) - 1;
        message[i] = modd(message[i]+0.5, MODULO_LATTICE);
    }

}