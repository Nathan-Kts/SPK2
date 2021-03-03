#include "lattice_functions.h"

/*void create_lattice(){
    public_lattice.metadata.dim_n = VECTOR_SIZE;
    public_lattice.metadata.dim_m = NBR_VECTORS;
    public_lattice.metadata.max = MODULO_LATTICE;
    int i;

    for (i = 0; i<public_lattice.metadata.dim_n; i++) {
        public_lattice.vectors[i] = rand()%public_lattice.metadata.max;
    }//end if
}//end create_lattice()*/

void build_new_lattice(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice_2[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j;
    for(i = 0; i < VECTOR_SIZE; i++){
        for(j = 0; j < VECTOR_SIZE; j++){
            private_lattice_2[i][j] = rand()%MODULO_LATTICE;
        }
    }
    for(i = 0; i < VECTOR_SIZE-1; i++){
        int vector = rand()%VECTOR_SIZE;
        for(j = 0; j < VECTOR_SIZE; j++)
            private_lattice_2[vector][j] = public_lattice[vector][j];
    }
}

void create_polynome(long input[]){
    long i;
    for(i = 0; i < VECTOR_SIZE; i++) {
        input[i]=rand()%MODULO_LATTICE;
    }//end for
}//end create_polynome()

void public_generation(double private_lattice[VECTOR_SIZE][VECTOR_SIZE], double public_lattice[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j, k, multiplier;
    for(i = 0; i < VECTOR_SIZE; i++){
        for(j = i; j < VECTOR_SIZE; j++) {
            multiplier = rand() % 10;
            for(k = 0; k < VECTOR_SIZE; k++)
                public_lattice[i][k] += multiplier * private_lattice[j][k];
        }
    }
}

void private_generation(double public_lattice[VECTOR_SIZE][VECTOR_SIZE], double private_lattice[VECTOR_SIZE][VECTOR_SIZE]){
    int i;
    for(i = 0; i < VECTOR_SIZE; i++) {

    }
}