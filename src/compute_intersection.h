//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_COMPUTE_INTERSECTION_H
#define TFE_KEM_COMPUTE_INTERSECTION_H

#include "gaus_elimination.c"

void dual(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]);
void concatenate(int nbr_vectors, int vector_size, double lattice1[nbr_vectors][vector_size], double lattice2[nbr_vectors][vector_size], double output[2*nbr_vectors][vector_size]);
void get_half_of_matrix(int nbr_vectors, int vector_size, double input[2*nbr_vectors][vector_size], double output[nbr_vectors][vector_size]);
void intersection_lattice(int nbr_vectors, int vector_size, double lattice1[nbr_vectors][vector_size], double lattice2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]);

#endif //TFE_KEM_COMPUTE_INTERSECTION_H
