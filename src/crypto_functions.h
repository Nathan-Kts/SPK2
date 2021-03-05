//
// Created by Nathan on 05/03/2021.
//

#ifndef TFE_KEM_CRYPTO_FUNCTIONS_H
#define TFE_KEM_CRYPTO_FUNCTIONS_H

void decode(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]);
void decoding(int vector_size, double message[vector_size]);
void noise_maker(int vector_size, double message[vector_size]);

#endif //TFE_KEM_CRYPTO_FUNCTIONS_H
