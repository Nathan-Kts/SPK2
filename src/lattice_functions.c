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

void build_new_lattice(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice_2[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++){
        for(j = 0; j < VECTOR_SIZE; j++){
            private_lattice_2[i][j] = rand()%MODULO_LATTICE;
        }
    }
    for(i = 0; i < VECTOR_SIZE-1; i++){
        int vector = rand()%VECTOR_SIZE;
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice_2[vector][j] = public_lattice[vector][j];
    }
}

void create_polynome(long input[]){
    long i;
    for(i = 0; i < VECTOR_SIZE; i++) {
        input[i]=rand()%MODULO_LATTICE;
    }//end for
}//end create_polynome()

void public_generation(double private_lattice[VECTOR_SIZE][VECTOR_SIZE], double public_lattice[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j, k, multiplier;
    for(i = 0; i < VECTOR_SIZE; i++)
        for(j = 0; j < VECTOR_SIZE; j++)
            public_lattice[i][j] = 0;
    for(i = 0; i < VECTOR_SIZE; i++){
        for(j = i; j < VECTOR_SIZE; j++) {
            multiplier = (rand() % 5)+1;
            for(k = 0; k < VECTOR_SIZE; k++) {
                public_lattice[i][k] += multiplier * private_lattice[j][k];
                //printf("%10.4f %d %10.4f %d %d %d\n", public_lattice[i][k], multiplier, private_lattice[j][k], i, j, k);
            }
        }
        for(k = 0; k < VECTOR_SIZE; k++)
            public_lattice[i][k] = modd(public_lattice[i][k]+1, MODULO_LATTICE);
    }
}

/**
 * @brief
 * @param message
 */
void decoding(double message[VECTOR_SIZE]){
    int i;
    for(i = 0; i < VECTOR_SIZE; i++) {
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
void noise_maker(double message[VECTOR_SIZE]){
    int i;
    for(i = 0; i < VECTOR_SIZE; i++) {
        message[i] += (rand() % 3) - 1;
        message[i] = modd(message[i]+0.5, MODULO_LATTICE);
    }

}