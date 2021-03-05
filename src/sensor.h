//
// Created by Nathan on 05/03/2021.
//

#ifndef TFE_KEM_SENSOR_H
#define TFE_KEM_SENSOR_H

#include "public_to_private.h"
#include "lattice_functions.h"
#include "compute_intersection.h"

void sensor(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double intersection[nbr_vectors][vector_size]);

#endif //TFE_KEM_SENSOR_H
