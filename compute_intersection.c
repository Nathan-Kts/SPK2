#include "compute_intersection.h"

void dual(int n, int m, double input[n][m], double output[n][m]){
    double temp2[n][m];

    product_matrix_prime_matrix(input, input, output);
    inversion_matrix(output, temp2);
    product_matrix_matrix(input, temp2, output);
}

void concatenate(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]) {
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++)
        for(j = 0; j < VECTOR_SIZE; j++){
            output[i][j] = lattice1[i][j];
            output[i][j+VECTOR_SIZE] = lattice2[i][j];
        }
}

void get_half_of_matrix(double input[2*VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++)
        for(j = 0; j < VECTOR_SIZE; j++){
            output[i][j] = input[i][j];
        }
}


void intersection_lattice(double lattice1[VECTOR_SIZE][VECTOR_SIZE], double lattice2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]) {
    double dual_lattice1[VECTOR_SIZE][VECTOR_SIZE], dual_lattice2[VECTOR_SIZE][VECTOR_SIZE];
    double temp[VECTOR_SIZE][2*VECTOR_SIZE];
    dual(VECTOR_SIZE, VECTOR_SIZE, lattice1, dual_lattice1);
    dual(VECTOR_SIZE, VECTOR_SIZE, lattice2, dual_lattice2);
    concatenate(dual_lattice1, dual_lattice1, temp);
    gauss_elimination(VECTOR_SIZE, 2*VECTOR_SIZE, temp);
    get_half_of_matrix(temp, dual_lattice1);
    //print_matrix(VECTOR_SIZE, VECTOR_SIZE, dual_lattice1);
    dual(VECTOR_SIZE, VECTOR_SIZE, dual_lattice1, output);
}
