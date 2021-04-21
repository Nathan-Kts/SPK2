#include "sensor.h"
#include "gaus_elimination.h"
#include "public_to_private.h"

void sensor(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double intersection[nbr_vectors][vector_size]){
    double new_public_lattice[nbr_vectors][vector_size];


    // creation of new Private lattice with common points
    //really bad public_to_new_private(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //really bad public_to_new_private_copy_half(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //really bad public_to_new_private_random_change(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    public_to_new_private_best_idea(nbr_vectors, vector_size, received_public_lattice, new_private_lattice, new_public_lattice);
    //public_to_new_private_one_vector(nbr_vectors, vector_size, received_public_lattice, new_private_lattice, new_public_lattice);

    //printf("New private matrix : \n");
    //print_matrix(nbr_vectors, vector_size, new_private_lattice);

    ////public_generation(nbr_vectors, vector_size, new_private_lattice, new_public_lattice);
    //printf("New public matrix : \n");
    //print_matrix(nbr_vectors, vector_size, new_public_lattice);

    intersection_lattice(nbr_vectors, vector_size, received_public_lattice, new_public_lattice, intersection);

    //TODO maybe leave it uncommented
    // gauss_elimination(nbr_vectors, vector_size, intersection);

    //TODO for(int i=0;i<nbr_vectors;i++)
    //    for(int j=0;j<vector_size;j++)
    //        intersection[i][j] = modd(intersection[i][j], MODULO_LATTICE);

    //printf("Intersection matrix : \n");
    //print_matrix(nbr_vectors, vector_size, intersection);

}