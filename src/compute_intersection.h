//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_COMPUTE_INTERSECTION_H
#define TFE_KEM_COMPUTE_INTERSECTION_H

#include "gaus_elimination.c"

void intersection_lattice(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void dual(int n, int m, double input[n][m], double output[n][m]);
void concatenate(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void get_half_of_matrix(double input[2*VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);

#endif //TFE_KEM_COMPUTE_INTERSECTION_H
