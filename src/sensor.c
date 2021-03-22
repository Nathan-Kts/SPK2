#include "sensor.h"
#include "gaus_elimination.h"

void sensor(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double intersection[nbr_vectors][vector_size]){
    double new_public_lattice[nbr_vectors][vector_size];

    //public_to_new_private(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //public_to_new_private_copy_half(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //public_to_new_private_random_change(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);


    //printf("New private matrix : \n");
    //print_matrix(nbr_vectors, vector_size, new_private_lattice);

    public_generation(nbr_vectors, vector_size, new_private_lattice, new_public_lattice);
    //printf("New public matrix : \n");
    //print_matrix(nbr_vectors, vector_size, new_public_lattice);

    intersection_lattice(nbr_vectors, vector_size, received_public_lattice, new_public_lattice, intersection);

    gauss_elimination(nbr_vectors, vector_size, intersection);

    //printf("Intersection matrix : \n");
    //print_matrix(nbr_vectors, vector_size, intersection);

}