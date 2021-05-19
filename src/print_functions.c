//
// Created by Nathan on 03/03/2021.
//
#include "print_functions.h"

void print_matrix(int n, int m, double matrix[n][m]){
    int i,j;
    for(i=0; i<n; i++){
        for(j=0; j<m; j++)
            printf("%20.6f", matrix[i][j]);
        printf("\n");
    }
    printf("\n");

}

void print_vector(int n, double vector[n]){
    int i;
    for(i=0; i<n; i++)
            printf("%20.2f", vector[i]);
    printf("\n");
}

void print_final_output(int n, double secret[n], double decoded_1[n], double decoded_2[n]){
    for (int i = 0; i < n; ++i) {
        if (secret[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (secret[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (secret[i] > MODULO_LATTICE/4 && secret[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        if (decoded_1[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_1[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_1[i] > MODULO_LATTICE/4 && decoded_1[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (decoded_2[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_2[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_2[i] > MODULO_LATTICE/4 && decoded_2[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");
}

void print_final_output_long(int n, double secret[n], double decoded_0[n], double decoded_1[n], double decoded_2[n], double decoded_3[n], double decoded_pirate[n]){
    for (int i = 0; i < n; ++i) {
        if (secret[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (secret[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (secret[i] > MODULO_LATTICE/4 && secret[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        if (decoded_0[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_0[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_0[i] > MODULO_LATTICE/4 && decoded_0[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        if (decoded_1[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_1[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_1[i] > MODULO_LATTICE/4 && decoded_1[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        if (decoded_2[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_2[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_2[i] > MODULO_LATTICE/4 && decoded_2[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");

    for (int i = 0; i < n; ++i) {
        if (decoded_3[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_3[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_3[i] > MODULO_LATTICE/4 && decoded_3[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");
    for (int i = 0; i < n; ++i) {
        if (decoded_pirate[i] <= MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        else if (decoded_pirate[i] >= 3*MODULO_LATTICE/4)
            printf("%20.2f", 0.0);
        if (decoded_pirate[i] > MODULO_LATTICE/4 && decoded_pirate[i] < 3*MODULO_LATTICE/4)
            printf("%20.2f", 1.0);
    }
    printf("\n");
}