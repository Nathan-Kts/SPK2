#include <stdio.h>
#include "parameters.h"
#include "lattice_functions.c"
#include "print_functions.c"
void main()
{
    double private_lattice[VECTOR_SIZE][VECTOR_SIZE], public_lattice[VECTOR_SIZE][VECTOR_SIZE];

    create_random_lattice(VECTOR_SIZE, VECTOR_SIZE, private_lattice);
    printf("Private matrix : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, private_lattice);

    public_generation(private_lattice, public_lattice);

    printf("Public matrix : \n");
    print_matrix(VECTOR_SIZE, VECTOR_SIZE, public_lattice);

    double private_lattice2[VECTOR_SIZE][VECTOR_SIZE], public_lattice2[VECTOR_SIZE][VECTOR_SIZE];

    public_to_new_private(public_lattice, private_lattice2);


}//end main()
