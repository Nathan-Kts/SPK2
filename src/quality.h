//
// Created by Nathan on 15/03/2021.
//

#ifndef TFE_KEM_QUALITY_H
#define TFE_KEM_QUALITY_H

#include "math_functions.h"


double max_norm(int nbr_vectors, int vector_size, double **input);
void gram_schimdt_modif(int nbr_vectors, int vector_size, double A[nbr_vectors][vector_size], double Q[nbr_vectors][vector_size]);

#endif //TFE_KEM_QUALITY_H
