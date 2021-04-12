//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_PUBLIC_TO_PRIVATE_H
#define TFE_KEM_PUBLIC_TO_PRIVATE_H

#include "parameters.h"
#include "math_functions.h"

void public_to_new_private(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice[nbr_vectors][vector_size]);
void public_to_new_private_copy_half(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice[nbr_vectors][vector_size]);
void public_to_new_private_random_change(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double private_lattice_2[nbr_vectors][vector_size]);
void public_to_new_private_best_idea(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double new_public_lattice[nbr_vectors][vector_size]);
void public_to_new_private_one_vector(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double new_public_lattice[nbr_vectors][vector_size]);

#endif //TFE_KEM_PUBLIC_TO_PRIVATE_H
