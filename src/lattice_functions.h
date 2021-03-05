//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_LATTICE_FUNCTIONS_H
#define TFE_KEM_LATTICE_FUNCTIONS_H

#include "parameters.h"
#include "math_functions.h"

void create_random_lattice(int n, int m, double output[n][m]);
void public_generation(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]);


#endif //TFE_KEM_LATTICE_FUNCTIONS_H
