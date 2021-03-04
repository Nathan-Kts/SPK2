//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_LATTICE_FUNCTIONS_H
#define TFE_KEM_LATTICE_FUNCTIONS_H

#include "parameters.h"
#include "math_functions.h"

void build_new_lattice(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice_2[VECTOR_SIZE][VECTOR_SIZE]);
void create_random_lattice(int n, int m, double output[n][m]);
void create_polynome(long input[]);
void public_generation(double private_lattice[VECTOR_SIZE][VECTOR_SIZE], double public_lattice[VECTOR_SIZE][VECTOR_SIZE]);
void private_generation(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice[VECTOR_SIZE][VECTOR_SIZE]);

#endif //TFE_KEM_LATTICE_FUNCTIONS_H
