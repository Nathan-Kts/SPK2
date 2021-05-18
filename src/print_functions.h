//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_PRINT_FUNCTIONS_H
#define TFE_KEM_PRINT_FUNCTIONS_H

#include <stdio.h>
#include "parameters.h"

void print_matrix(int m, int n, double matrix[m][n]);
void print_vector(int n, double vector[n]);
void print_final_output(int n, double secret[n], double decoded_1[n], double decoded_2[n]);

#endif //TFE_KEM_PRINT_FUNCTIONS_H
