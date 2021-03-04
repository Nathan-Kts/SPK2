//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_MATH_FUNCTIONS_H
#define TFE_KEM_MATH_FUNCTIONS_H

#include "parameters.h"
#include <math.h>

double exp(double input);
long mod(long a, int b);
double modd(double a, int b);
int msb(int n);
double log(double input);
double round(double input);
double product_vector_vector(int nbr_vectors, int vector_size, double vector_1[nbr_vectors][vector_size], int line_1, double vector_2[nbr_vectors][vector_size], int line_2, int size);
void product_matrix_prime_matrix(int nbr_vectors, int vector_size, double matrix_1[nbr_vectors][vector_size], double matrix_2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]);
void product_matrix_matrix(int nbr_vectors, int vector_size, double matrix_1[nbr_vectors][vector_size], double matrix_2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]);
void product_matrix_vector(int nbr_vectors, int vector_size, double matrix[nbr_vectors][vector_size], double vector[vector_size], double output[vector_size]);
void inversion_matrix(int vector_size, double matrix[vector_size][vector_size], double output[vector_size][vector_size]);

#endif //TFE_KEM_MATH_FUNCTIONS_H
