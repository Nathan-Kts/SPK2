#include "lattice_functions.h"
#include "gaus_elimination.h"
#include "math_functions.h"
#include "print_functions.h"
#include "random.h"

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
                output[i][j] = rand()%(MODULO_LATTICE/4); //TODO change back tà MODDULO_LATTICE/1000
}//end create_lattice()

void create_private_lattice(int nbr_vectors, int vector_size, double output[nbr_vectors][vector_size]) {
    int i, j;

    for (i = 0; i < nbr_vectors; i++)
        for (j = 0; j < vector_size; j++)
            if (i == j)
                output[i][j] = random_double(PRIVATE_LATTICE_LIMIT) + 1;
            else
                output[i][j] = 0;
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);

    //gram_schimdt(nbr_vectors, output);

    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);
}

void create_private_lattice2(int nbr_vectors, int vector_size, double output[nbr_vectors][vector_size]) {
    int i, j;

    for (i = 0; i < nbr_vectors; i++)
        for (j = 0; j < vector_size; j++)
            if (i == j)
                output[i][j] = random_double(PRIVATE_LATTICE_LIMIT) + 1;

    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);

    //gram_schimdt(nbr_vectors, output);

    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);
    for(int i=0;i<nbr_vectors;i++)
        for(int j=0;j<vector_size;j++)
            output[i][j] = modd(output[i][j], MODULO_LATTICE);
}

void unimodular_generation(int nbr_vectors, int vector_size, double unimodular[nbr_vectors][vector_size]){
    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            if (i == j)
                unimodular[i][j] = 1;
            else if (i < j)
                unimodular[i][j] = random_double(PUBLIC_LATTICE_LIMIT)-PUBLIC_LATTICE_LIMIT/2;
            else if (j < i)
                unimodular[i][j] = 0;
        }
    }
#if defined(PRINT_MATRICES)
    //printf("Unimodular :\n");
    //print_matrix(nbr_vectors, nbr_vectors, unimodular);
#endif
}

void public_generation(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size], double unimodular[nbr_vectors][vector_size]){
    /*int i, j, k, multiplier;
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            public_lattice[i][j] = private_lattice[i][j];
    gauss_elimination(nbr_vectors, vector_size, public_lattice);
    for(k = 0; k < vector_size; k++)
        public_lattice[i][k] = modd(public_lattice[i][k]+1, MODULO_LATTICE);*/

    unimodular_generation(nbr_vectors, vector_size, unimodular);
    product_matrix_matrix(nbr_vectors, vector_size, unimodular, private_lattice, public_lattice);

    //for(int i = 0; i < nbr_vectors; i++)
    //    for(int j = 0; j < vector_size; j++)
    //        public_lattice[i][j] = private_lattice[i][j];
    //gauss_elimination(nbr_vectors, vector_size, public_lattice);


    int i, j, k;/*
    double multiplier;
    // Initialize to 0 all elements of output lattice
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            public_lattice[i][j] = 0;

    // take an vector and copies that on and the next ones from the input lattice mutliplied by an random integer
    for(i = 0; i < nbr_vectors; i++){
        for(j = i; j < nbr_vectors; j++) {
            multiplier = rand() % 20;
            printf("%f\n", multiplier);
            for(k = 0; k < vector_size; k++) {
                public_lattice[i][k] += multiplier * private_lattice[j][k]; //multiplier *
                //printf("%10.4f %d %10.4f %d %d %d\n", public_lattice[i][k], multiplier, private_lattice[j][k], i, j, k);
            }
        }
        //for(k = 0; k < vector_size; k++)
        //    public_lattice[i][k] = modd(public_lattice[i][k], MODULO_LATTICE);
    }*/

    //printf("dd\n");
    //print_matrix(nbr_vectors, vector_size, private_lattice);

    ///Test to see if the lattices are the same
    /*double private_lattice_test[NBR_VECTORS][VECTOR_SIZE], public_lattice_test[NBR_VECTORS][VECTOR_SIZE];
    double output_private[NBR_VECTORS][VECTOR_SIZE], output_public[NBR_VECTORS][VECTOR_SIZE];
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++)
            private_lattice_test[i][j] = private_lattice[i][j];
            public_lattice_test[i][j] = public_lattice[i][j];
    product_matrix_prime_matrix(nbr_vectors, vector_size, private_lattice, private_lattice, output_private);
    product_matrix_prime_matrix(nbr_vectors, vector_size, public_lattice, public_lattice, output_public);

    gauss_elimination(nbr_vectors, vector_size, output_private);
    gauss_elimination(nbr_vectors, vector_size, output_public);

    float test_public = 1.0;
    float test_private = 1.0;
    for(i = 0; i < nbr_vectors; i++){
        test_private *= output_private[i][i];
        //printf("%f et %f\n", test_private, output_private[i][i]);
        test_public *= output_public[i][i];
        //printf("%f et %f\n", test_public, output_public[i][i]);
    }
    //float trol = abs(test_public)/abs(test_private);
    //printf("The matrices have %f size and share %f%\n", test_private, trol);*/
}
