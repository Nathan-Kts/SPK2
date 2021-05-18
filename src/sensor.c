#include "sensor.h"
#include "gaus_elimination.h"
#include "public_to_private.h"
#include "print_functions.h"
#include "quality.h"

void sensor(int nbr_vectors, int vector_size, double received_public_lattice[nbr_vectors][vector_size], double new_private_lattice[nbr_vectors][vector_size], double intersection[nbr_vectors][vector_size]){
    double new_public_lattice[nbr_vectors][vector_size];

    //really bad public_to_new_private(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //really bad public_to_new_private_copy_half(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //really bad public_to_new_private_random_change(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //public_to_new_private_best_idea(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);
    //public_to_new_private_one_vector(nbr_vectors, vector_size, received_public_lattice, new_private_lattice, new_public_lattice);
    public_to_new_private_start_ortho(nbr_vectors, vector_size, received_public_lattice, new_private_lattice);

    int max_amount = 0;
    while(1){
        double unimodular[nbr_vectors][vector_size];
        public_generation(nbr_vectors, vector_size, new_private_lattice, intersection, unimodular);
        double ratio = hadamard_ratio(nbr_vectors, intersection);
        //printf("Ratio %f\n", ratio);
        if (((ratio <= HADAMARD_RATIO || max_amount > 10) && not_null_response(nbr_vectors, intersection)==1)||max_amount > 100){
            break;
        }
        max_amount += 1;
    }
    //print_matrix(nbr_vectors, nbr_vectors, received_public_lattice);
    intersection_lattice(nbr_vectors, vector_size, received_public_lattice, new_public_lattice, intersection);
    //print_matrix(nbr_vectors, nbr_vectors, intersection);
    gauss_elimination(nbr_vectors, vector_size, intersection);
    //print_matrix(nbr_vectors, nbr_vectors, intersection);

    for(int i=0;i<nbr_vectors;i++) {
        for (int j = 0; j < vector_size; j++)
            intersection[i][j] = modd(intersection[i][j], MODULO_LATTICE);
        if(intersection[i][i] < 0.1)
            intersection[i][i] = 17.0;
    }




#if defined(PRINT_MATRICES)
    printf("Private lattice from sensor\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, new_private_lattice);
    printf("Public lattice from sensor\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection);
#endif
}