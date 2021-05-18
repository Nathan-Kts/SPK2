#include "public_to_private.h"
#include "lattice_functions.h"
#include "quality.h"
#include "print_functions.h"
#include "gaus_elimination.h"
#include "random.h"

void public_to_new_private_best_idea(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size]){
    //create a random lattice
    //create_random_lattice(nbr_vectors, vector_size, new_private_lattice);
    create_private_lattice(nbr_vectors, vector_size, new_private_lattice);
    double old_base[nbr_vectors][vector_size];

    //printf("Length of private lattice random : %f - %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice, new_public_lattice), max_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice));

    //printf("Before %f\n", norm(nbr_vectors, vector_size, new_private_lattice));

    //for(int i = 0; i < 1; i++){
    int vecto = random_double(5)+1;
    //TODO Problem here, I have to find a way to be shure that the public lattice doens't have a empty or double line ! the problem here is that if this number is random it doesn't work
    printf("I choose to copy the %dth vector\n", vecto);
    for(int j = 0; j < vector_size; j++)
        new_private_lattice[vecto][j] = received_public_lattice[vecto][j];
    //}

    //printf("After %f\n", norm(nbr_vectors, vector_size, new_private_lattice));

    gram_schimdt(nbr_vectors, new_private_lattice);
    gauss_elimination(nbr_vectors, vector_size, new_private_lattice);

    //printf("Length of private lattice random with points : %f - %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice, new_public_lattice), max_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice));
}

void public_to_new_private_start_ortho(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size]){
    //create a random lattice
    //create_random_lattice(nbr_vectors, vector_size, new_private_lattice);
    create_private_lattice(nbr_vectors, vector_size, new_private_lattice);
    //double old_base[(int) (nbr_vectors / 2)][vector_size];

    //printf("Length of private lattice random : %f - %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice, new_public_lattice), max_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice));


    //for(int i = 0; i < 1; i++){
    int vecto = random_double(5)+1;
    printf("I choose to copy the %dth vector\n", vecto);
    for(int j = vecto; j < vector_size; j++) {
        if (received_public_lattice[vecto][j] != 0)
            new_private_lattice[j][j] = received_public_lattice[vecto][j];
        else
            new_private_lattice[j][j] = random_double(PRIVATE_LATTICE_LIMIT)+1;
    }
    //}


    //gram_schimdt(nbr_vectors, new_private_lattice);
    //gauss_elimination(nbr_vectors, vector_size, new_private_lattice);

    //printf("Length of private lattice random with points : %f - %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice, new_public_lattice), max_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice));
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

void public_to_new_private_one_vector(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double new_public_lattice[nbr_vectors][vector_size]){
    int i, j;
    for(i = 0; i < nbr_vectors; i++){
        for(j = 0; j < vector_size; j++){
            new_private_lattice[i][j] = 0;
        }
    }

    int vector = rand()%vector_size;
    for(j = 0; j < vector_size; j++){
            new_private_lattice[j][j] = received_public_lattice[vector][j];
    }


    printf("Length of private lattice : %f - %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice, new_public_lattice), max_norm(NBR_VECTORS, VECTOR_SIZE, new_private_lattice));

    double unimodular[nbr_vectors][vector_size];
    public_generation(nbr_vectors, vector_size, new_private_lattice, new_public_lattice, unimodular);
}

