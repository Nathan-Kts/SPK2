#include "lattice_functions.h"
#include "gaus_elimination.h"

/**
 * @brief Creates a random lattice
 * @param n
 * @param m
 * @param output
 */
void create_random_lattice(int n, int m, double output[n][m]){
    int i, j;

    for (i = 0; i<n; i++)
        for (j = 0; j < m; j++)
            if (i == j)
                output[i][j] = rand()%(MODULO_LATTICE); //TODO change back tà MODDULO_LATTICE/10
            else
                output[i][j] = rand()%(MODULO_LATTICE - 11); //TODO change back tà MODDULO_LATTICE/1000
}//end create_lattice()

void public_generation(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size]){
    /*int i, j, k, multiplier;
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            public_lattice[i][j] = private_lattice[i][j];
    gauss_elimination(nbr_vectors, vector_size, public_lattice);
    for(k = 0; k < vector_size; k++)
        public_lattice[i][k] = modd(public_lattice[i][k]+1, MODULO_LATTICE);*/


    int i, j, k, multiplier;
    // Initialize to 0 all elements of output lattice
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            public_lattice[i][j] = 0;

    // take an vector and copies that on and the next ones from the input lattice mutliplied by an random integer
    for(i = 0; i < nbr_vectors; i++){
        for(j = i; j < nbr_vectors; j++) {
            //multiplier = (rand() % 5)+1;
            for(k = 0; k < vector_size; k++) {
                public_lattice[i][k] += private_lattice[j][k]; //multiplier *
                //printf("%10.4f %d %10.4f %d %d %d\n", public_lattice[i][k], multiplier, private_lattice[j][k], i, j, k);
            }
        }
        for(k = 0; k < vector_size; k++)
            public_lattice[i][k] = modd(public_lattice[i][k], MODULO_LATTICE);
    }
    //TODO Add scrambling of vectors
}
