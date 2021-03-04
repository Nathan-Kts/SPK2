//
// Created by Nathan on 03/03/2021.
//

#ifndef TFE_KEM_PUBLIC_TO_PRIVATE_H
#define TFE_KEM_PUBLIC_TO_PRIVATE_H

#include "parameters.h"
#include "math_functions.h"

void public_to_new_private(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice[VECTOR_SIZE][VECTOR_SIZE]);

#endif //TFE_KEM_PUBLIC_TO_PRIVATE_H
