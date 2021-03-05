//
// Created by Nathan on 05/03/2021.
//

#include "gateway.h"

void gateway(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]){
    create_random_lattice(nbr_vectors, vector_size, private_lattice);
    //printf("Private matrix : \n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);

    public_generation(nbr_vectors, vector_size, private_lattice, public_lattice);
    //printf("Public matrix : \n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_1);
}