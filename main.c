#include <stdio.h>
#include <time.h>

#include "src/parameters.h"
#include "src/math_functions.c"
#include "src/lattice_functions.c"
#include "src/print_functions.c"
#include "src/public_to_private.c"
#include "src/compute_intersection.c"

int main()
{
    //Gateway
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE], public_lattice_1[NBR_VECTORS][VECTOR_SIZE];

    create_random_lattice(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);
    printf("Private matrix : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);

    public_generation(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, public_lattice_1);
    printf("Public matrix : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_1);

    //Sensor 1
    double private_lattice_2[NBR_VECTORS][VECTOR_SIZE], public_lattice_2[NBR_VECTORS][VECTOR_SIZE];
    //public_to_new_private(NBR_VECTORS, VECTOR_SIZE, public_lattice_1, private_lattice_2);
    //public_to_new_private_copy_half(NBR_VECTORS, VECTOR_SIZE, public_lattice_1, private_lattice_2);
    public_to_new_private_random_change(NBR_VECTORS, VECTOR_SIZE, public_lattice_1, private_lattice_2);


    printf("New private matrix : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_2);

    public_generation(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, public_lattice_2);
    printf("New public matrix : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_2);



    double intersection[NBR_VECTORS][VECTOR_SIZE];
    intersection_lattice(NBR_VECTORS, VECTOR_SIZE, public_lattice_1, public_lattice_2, intersection);

    gauss_elimination(NBR_VECTORS, VECTOR_SIZE, intersection);

    printf("Intersection matrix : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection);

    time_t t;
    srand((unsigned) time(&t));
    int i;
    double secret[VECTOR_SIZE];
    for (i = 0; i < VECTOR_SIZE; ++i)
        secret[i] = 32*(rand()%2);

    double message[VECTOR_SIZE];
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, intersection, secret, message);
    noise_maker(VECTOR_SIZE, message);
    printf("Broadcast Message : \n");
    print_vector(VECTOR_SIZE, message);

    double decode_1[VECTOR_SIZE];
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, message, decode_1);
    printf("Message decoded by 1 : \n");
    print_vector(VECTOR_SIZE, decode_1);
    decoding(VECTOR_SIZE, decode_1);
    print_vector(VECTOR_SIZE, decode_1);

    double decode_2[VECTOR_SIZE];
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, message, decode_2);
    printf("Message decoded by 2 : \n");
    print_vector(VECTOR_SIZE, decode_2);
    decoding(VECTOR_SIZE, decode_2);
    print_vector(VECTOR_SIZE, decode_2);

    int j = 0;
    for (i = 0; i < VECTOR_SIZE; ++i) {
        if(decode_1[i] == decode_2[i])
            j++;
    }
    printf("Number of good decryption : %d/%d", j, VECTOR_SIZE);

    
}//end main()
