#include "public_to_private.h"

void public_to_new_private_alwen_peikert(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double new_public_lattice[nbr_vectors][vector_size]){
    double old_base[(int) (nbr_vectors / 2)][vector_size];
    for (int i = 0; i < (int) (nbr_vectors/2); ++i) {
        for (int j = 0; j < vector_size; ++j) {
            old_base[i][j] = received_public_lattice[i][j];
        }
    }



}

/**
 * @brief
 * @param public_lattice
 * @param private_lattice
 */
void public_to_new_private(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice[nbr_vectors][vector_size]){
    int i, j;
    for(i = 0; i < nbr_vectors; i=i+2) {
        for(j = 0; j < vector_size; j++)
            private_lattice[(int) (i/2)][j] = modd(public_lattice[i][j]+public_lattice[i+1][j], MODULO_LATTICE);
    }
    for(i = (int) (nbr_vectors/2); i < nbr_vectors; i++) {
        for(j = 0; j < vector_size; j++)
            private_lattice[i][j] = rand()%MODULO_LATTICE;
    }
}

void public_to_new_private_copy_half(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice[nbr_vectors][vector_size]){
    int i, j;
    for(i = 0; i < (int) (nbr_vectors/2); i++) {
        for(j = 0; j < vector_size; j++)
            private_lattice[i][j] = modd(public_lattice[i][j],MODULO_LATTICE);
    }
    for(i = (int) (nbr_vectors/2); i < nbr_vectors; i++) {
        for(j = 0; j < vector_size; j++)
            private_lattice[i][j] = rand()%MODULO_LATTICE;
    }
}

void public_to_new_private_random_change(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice_2[nbr_vectors][vector_size]){
    int i, j;
    for(i = 0; i < nbr_vectors; i++){
        for(j = 0; j < vector_size; j++){
            private_lattice_2[i][j] = rand()%MODULO_LATTICE;
        }
    }
    for(i = 0; i < nbr_vectors-1; i++){
        int vector = rand()%vector_size;
        for(j = 0; j < vector_size; j++)
            private_lattice_2[vector][j] = public_lattice[vector][j];
    }
}

