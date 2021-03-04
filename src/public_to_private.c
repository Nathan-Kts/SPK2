#include "public_to_private.h"

/**
 * @brief
 * @param public_lattice
 * @param private_lattice
 */
void public_to_new_private(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i=i+2) {
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice[(int) (i/2)][j] = modd(public_lattice[i][j]+public_lattice[i+1][j], MODULO_LATTICE);
    }
    for(i = (int) (VECTOR_SIZE/2); i < VECTOR_SIZE; i++) {
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice[i][j] = rand()%MODULO_LATTICE;
    }
}

void public_to_new_private_copy_half(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < (int) (VECTOR_SIZE/2); i++) {
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice[i][j] = modd(public_lattice[i][j],MODULO_LATTICE);
    }
    for(i = (int) (VECTOR_SIZE/2); i < VECTOR_SIZE; i++) {
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice[i][j] = rand()%MODULO_LATTICE;
    }
}