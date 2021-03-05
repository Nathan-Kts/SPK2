#include <stdio.h>
#include <time.h>
#include <crypto_functions.h>
#include <sensor.h>
#include <gateway.h>

#include "src/parameters.h"
#include "src/math_functions.c"
#include "src/lattice_functions.c"
#include "src/print_functions.c"
#include "src/public_to_private.c"
#include "src/compute_intersection.c"

int main()
{
    //Gateway
    double private_lattice_g[NBR_VECTORS][VECTOR_SIZE], public_lattice_g[NBR_VECTORS][VECTOR_SIZE];
    gateway(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, public_lattice_g);

    //Sensor 1
    double intersection_1[NBR_VECTORS][VECTOR_SIZE], intersection_2[NBR_VECTORS][VECTOR_SIZE];
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE], private_lattice_2[NBR_VECTORS][VECTOR_SIZE];

    sensor(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, private_lattice_1, intersection_1);
    sensor(NBR_VECTORS, VECTOR_SIZE, intersection_1, private_lattice_2, intersection_2);

    //Broadcast
    time_t t;
    srand((unsigned) time(&t));
    int i;
    double secret[VECTOR_SIZE];
    for (i = 0; i < VECTOR_SIZE; ++i)
        secret[i] = (MODULO_LATTICE/2)*(rand()%2);

    double message[VECTOR_SIZE];
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, intersection_2, secret, message);
    noise_maker(VECTOR_SIZE, message);
    printf("Broadcast Message : \n");
    print_vector(VECTOR_SIZE, message);

    //Decode
    double decode_1[VECTOR_SIZE], decode_2[VECTOR_SIZE];
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, message, decode_1);
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, message, decode_2);

    int j = 0;
    for (i = 0; i < VECTOR_SIZE; ++i) {
        if(decode_1[i] == decode_2[i])
            j++;
    }
    printf("Number of good decryption : %d/%d", j, VECTOR_SIZE);

    
}//end main()
