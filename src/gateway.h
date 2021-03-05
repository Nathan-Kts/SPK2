//
// Created by Nathan on 05/03/2021.
//

#ifndef TFE_KEM_GATEWAY_H
#define TFE_KEM_GATEWAY_H

#include "lattice_functions.h"

void gateway(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]);

#endif //TFE_KEM_GATEWAY_H
