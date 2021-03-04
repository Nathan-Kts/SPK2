#include "compute_intersection.h"

/**
 * @brief Computes the dual of a specified lattice and writtes it in output
 * @param n the number of vectors in the lattice
 * @param m the size of each vector in the lattice (dimension of the vectors)
 * @param input the lattice for which we search the dual
 * @param output the dual of the input
 */
void dual(int n, int m, double input[n][m], double output[n][m]){
    double temp[n][m];

    /*printf("Entry : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, input);*/

    product_matrix_prime_matrix(input, input, output);

    /*printf("product 1 : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, output);*/

    inversion_matrix(output, temp); //proble !!!

    /*printf("Inversion : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, temp);*/

    product_matrix_matrix(input, temp, output);

    /*printf("Final matrix product : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, output);*/
}

/**
 * @brief Concatenates two lattices together to form a new one with twice as much vectors
 * @param lattice1 first lattice
 * @param lattice2 second lattice
 * @param output the new lattice
 */
void concatenate(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[2*VECTOR_SIZE][VECTOR_SIZE]) {
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++)
        for(j = 0; j < VECTOR_SIZE; j++){
            output[i][j] = lattice1[i][j];
            output[i+VECTOR_SIZE][j] = lattice2[i][j];
        }
}

/**
 * @brief After getting the hermit normal form, this allows to take only the interesting part
 * @param input the lattice with too much vectors (some are =  to 0)
 * @param output the new lattice
 */
void get_half_of_matrix(double input[2*VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++)
        for(j = 0; j < VECTOR_SIZE; j++){
            output[i][j] = input[i][j];
        }
}

/**
 * @brief Computes the intersection of two lattices
 * @param lattice1 first lattice
 * @param lattice2 second lattice
 * @param output output lattice
 */
void intersection_lattice(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]) {
    double dual_lattice1[VECTOR_SIZE][VECTOR_SIZE], dual_lattice2[VECTOR_SIZE][VECTOR_SIZE];
    double temp[2*VECTOR_SIZE][VECTOR_SIZE];
    dual(VECTOR_SIZE, VECTOR_SIZE, lattice1, dual_lattice1);
    dual(VECTOR_SIZE, VECTOR_SIZE, lattice2, dual_lattice2);
    concatenate(dual_lattice1, dual_lattice2, temp);

    /*printf("Concatenation of duals : \n");
    print_matrix(2*VECTOR_SIZE, VECTOR_SIZE, temp);*/

    gauss_elimination(2*VECTOR_SIZE, VECTOR_SIZE, temp);

    get_half_of_matrix(temp, dual_lattice1);

    /*printf("half of it: \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, dual_lattice1);*/
    dual(VECTOR_SIZE, VECTOR_SIZE, dual_lattice1, output);
}
