#include "compute_intersection.h"

/**
 * @brief Computes the dual of a specified lattice and writes it in output
 * @warning Matrix has to be squared
 * @param nbr_vectors the number of vectors in the lattice
 * @param m the size of each vector in the lattice (dimension of the vectors)
 * @param input the lattice for which we search the dual
 * @param output the dual of the input
 */
void dual(int nbr_vectors, int vector_size, double input[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]){
    double temp[nbr_vectors][vector_size];

    if(vector_size != nbr_vectors){
        printf("Matrices not square for dual !");
        exit(42);
    }

    /*printf("Entry : \n");
    print_matrix(nbr_vectors, vector_size, input);*/

    product_matrix_prime_matrix(nbr_vectors, vector_size, input, input, output);

    /*printf("product 1 : \n");
    print_matrix(nbr_vectors, vector_size, output);*/

    inversion_matrix(vector_size, output, temp);

    /*printf("Inversion : \n");
    print_matrix(nbr_vectors, vector_size, temp);*/

    product_matrix_matrix(nbr_vectors, vector_size, input, temp, output);

    /*printf("Final matrix product : \n");
    print_matrix(nbr_vectors, vector_size, output);*/
}

/**
 * @brief Concatenates two lattices together to form a new one with twice as much vectors
 * @param lattice1 first lattice
 * @param lattice2 second lattice
 * @param output the new lattice
 */
void concatenate(int nbr_vectors, int vector_size, double lattice1[nbr_vectors][vector_size], double lattice2[nbr_vectors][vector_size], double output[2*nbr_vectors][vector_size]) {
    int i, j;
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++){
            output[i][j] = lattice1[i][j];
            output[i+nbr_vectors][j] = lattice2[i][j];
        }
}

/**
 * @brief After getting the hermit normal form, this allows to take only the interesting part
 * @param input the lattice with too much vectors (some are =  to 0)
 * @param output the new lattice
 */
void get_half_of_matrix(int nbr_vectors, int vector_size, double input[2*nbr_vectors][vector_size], double output[nbr_vectors][vector_size]){
    int i, j;
    for(i = 0; i < nbr_vectors; i++)
        for(j = 0; j < vector_size; j++){
            output[i][j] = input[i][j];
        }
}

/**
 * @brief Computes the intersection of two lattices
 * @param lattice1 first lattice
 * @param lattice2 second lattice
 * @param output output lattice
 */
void intersection_lattice(int nbr_vectors, int vector_size, double lattice1[nbr_vectors][vector_size], double lattice2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]) {
    double dual_lattice1[nbr_vectors][vector_size], dual_lattice2[nbr_vectors][vector_size];
    double temp[2*nbr_vectors][vector_size];
    dual(nbr_vectors, vector_size, lattice1, dual_lattice1);
    dual(nbr_vectors, vector_size, lattice2, dual_lattice2);
    concatenate(nbr_vectors, vector_size, dual_lattice1, dual_lattice2, temp);

    /*printf("Concatenation of duals : \n");
    print_matrix(2*VECTOR_SIZE, VECTOR_SIZE, temp);*/

    gauss_elimination(2*nbr_vectors, vector_size, temp);

    get_half_of_matrix(nbr_vectors, vector_size, temp, dual_lattice1);

    /*printf("half of it: \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, dual_lattice1);*/
    dual(nbr_vectors, vector_size, dual_lattice1, output);
}
