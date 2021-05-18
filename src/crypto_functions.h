//
// Created by Nathan on 05/03/2021.
//

#ifndef TFE_KEM_CRYPTO_FUNCTIONS_H
#define TFE_KEM_CRYPTO_FUNCTIONS_H

void decode(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]);
void decoding(int vector_size, double message[vector_size]);
void noise_maker(int vector_size, double message[vector_size]);
void nearest_plane(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]);
void secret_builder(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double secret[nbr_vectors], double message[nbr_vectors]);
int count_good_decrypt(int nbr_vectors, double secret[nbr_vectors], double decoded_message[nbr_vectors]);
void decrypt(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size], double message[nbr_vectors], double decoded_message[nbr_vectors]);
void decrypt_babai(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size], double message[nbr_vectors], double decoded_message[nbr_vectors]);

#endif //TFE_KEM_CRYPTO_FUNCTIONS_H
