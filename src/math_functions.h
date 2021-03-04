//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_MATH_FUNCTIONS_H
#define TFE_KEM_MATH_FUNCTIONS_H

#include "parameters.h"
#include <math.h>

double exp(double input);
int msb(int n);
double log(double input);
double round(double input);
double product_vector_vector(int nbr_vectors, int vector_size, double vector_1[nbr_vectors][vector_size], int line_1, double vector_2[nbr_vectors][vector_size], int line_2, int size);
void product_matrix_prime_matrix(int nbr_vectors, int vector_size, double matrix_1[VECTOR_SIZE][VECTOR_SIZE], double matrix_2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void product_matrix_matrix(int nbr_vectors, int vector_size, double matrix_1[VECTOR_SIZE][VECTOR_SIZE], double matrix_2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void inversion_matrix(int nbr_vectors, int vector_size, double matrix[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
long mod(long a, long b);
double modd(double a, int b);
void product_matrix_vector(int nbr_vectors, int vector_size, double matrix[VECTOR_SIZE][VECTOR_SIZE], double vector[VECTOR_SIZE], double output[VECTOR_SIZE]);

#endif //TFE_KEM_MATH_FUNCTIONS_H
