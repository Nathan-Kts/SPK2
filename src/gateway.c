#include "gateway.h"
#include "quality.h"

void gateway(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]) {

    create_private_lattice(nbr_vectors, vector_size, private_lattice);
    //printf("Private matrix : \n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);
    double ratiop = hamdamard_ratio(nbr_vectors, private_lattice);
    printf("Ratio private : %f\n", ratiop);
    while(1){
        double unimodular[nbr_vectors][vector_size];
        public_generation(nbr_vectors, vector_size, private_lattice, public_lattice, unimodular);
        double ratio = hamdamard_ratio(nbr_vectors, public_lattice);
        printf("Ratio %f\n", ratio);
        if (ratio <= HADAMARD_RATIO){
            break;
        }
    }

    //TODO gauss_elimination(nbr_vectors, vector_size, public_lattice);
    //TODO for(int i=0;i<nbr_vectors;i++)
    //    for(int j=0;j<vector_size;j++)
    //        public_lattice[i][j] = modd(public_lattice[i][j], MODULO_LATTICE);
    //printf("Public matrix : \n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_1);
}