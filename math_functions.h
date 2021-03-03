//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_MATH_FUNCTIONS_H
#define TFE_KEM_MATH_FUNCTIONS_H

double exp(double input);
int msb(int n);
double log(double y);
double round(double input);
double product_vector_vector(double a[VECTOR_SIZE][VECTOR_SIZE], int aa, double b[VECTOR_SIZE][VECTOR_SIZE], int bb, int size);
void product_matrix_prime_matrix(double input1[VECTOR_SIZE][VECTOR_SIZE], double input2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void product_matrix_matrix(double input1[VECTOR_SIZE][VECTOR_SIZE], double input2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
void inversion_matrix(double matrix[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]);
long mod(long a, long b);

#endif //TFE_KEM_MATH_FUNCTIONS_H
