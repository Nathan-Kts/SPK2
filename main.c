#include <stdio.h>
//#include <time.h>
#include <crypto_functions.h>
#include <sensor.h>
#include <gateway.h>

#include "src/parameters.h"
#include "src/math_functions.c"
#include "src/lattice_functions.c"
#include "src/print_functions.c"
#include "src/public_to_private.c"
#include "src/compute_intersection.c"
//#include "src/HNF.c"
#include "quality.c"

//#define TEST
#define NBR_TEST 1000

int main()
{
    //Gateway
    double private_lattice_g[NBR_VECTORS][VECTOR_SIZE], public_lattice_g[NBR_VECTORS][VECTOR_SIZE];
    gateway(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, public_lattice_g);
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_g);


    /*double test[NBR_VECTORS][VECTOR_SIZE];
    gram_schimdt_modif(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, test);
    print_matrix(NBR_VECTORS, VECTOR_SIZE, test);

    double lc = 1/4;
    double hc = 3/4;
    double temp2[VECTOR_SIZE*NBR_VECTORS];

    for (int i = 0; i < NBR_VECTORS; ++i) {
        for (int j = 0; j < VECTOR_SIZE; ++j) {
            temp2[VECTOR_SIZE*i+j] = private_lattice_g[i][j];
        }
    }

    //lll_reduce(temp2, VECTOR_SIZE, lc, hc);*/

    //Sensor 1 and 2
    double intersection_1[NBR_VECTORS][VECTOR_SIZE], intersection_2[NBR_VECTORS][VECTOR_SIZE];
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE];//, private_lattice_2[NBR_VECTORS][VECTOR_SIZE];

    sensor(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, private_lattice_1, intersection_1); //TODO Normally public not private
    //sensor(NBR_VECTORS, VECTOR_SIZE, intersection_1, private_lattice_2, intersection_2);

    printf("Final intersection used to encrypt : \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_1);

#if defined(TEST)
    int total = 0;
    for(int count = 0; count < NBR_TEST; count++){
        srand(count);
#endif

    printf("Private g\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_g);
    printf("Public g\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_g);
    printf("Private 1\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);
    printf("Public 1\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_1);

    //Broadcast
    //time_t t;
    //srand((unsigned) time(&t));
    int i;
    double secret[VECTOR_SIZE];
    for (i = 0; i < VECTOR_SIZE; ++i)
        secret[i] = (MODULO_LATTICE / 2) * (rand() % 2);
    /*if(i%2==0)
        secret[i]=0;
    else
        secret[i]= MODULO_LATTICE/2;*/

    double message[VECTOR_SIZE];
    printf("Secret Message : \n");
    print_vector(VECTOR_SIZE, secret);

    //print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_2);
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, intersection_1, secret, message);
    noise_maker(VECTOR_SIZE, message);
    printf("Broadcast Message : \n");
    print_vector(VECTOR_SIZE, message);


    //Decode
    double decode_0[VECTOR_SIZE], decode_1[VECTOR_SIZE];//, decode_2[VECTOR_SIZE];
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, message, decode_0);
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, message, decode_1);
    //decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, message, decode_2);

    int j = 0;
    for (i = 0; i < VECTOR_SIZE; ++i) {
        if (decode_0[i] == decode_1[i])
            j++;
    }
    printf("Number of good decryption : %d/%d\n", j, VECTOR_SIZE);


    double temp[NBR_VECTORS][VECTOR_SIZE];
    printf("Length of private lattice g : %f and the public : %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, temp), gs_norm(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, temp));
    printf("Length of private lattice 1 : %f and the public : %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, temp), gs_norm(NBR_VECTORS, VECTOR_SIZE, intersection_1, temp));
    //printf("Length of private lattice 2 : %f - %f and the public : %f - %f\n", gram_schimdt_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, intersection_2), max_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_2), gram_schimdt_norm(NBR_VECTORS, VECTOR_SIZE, intersection_2, intersection_2), max_norm(NBR_VECTORS, VECTOR_SIZE, intersection_2));

#if defined(TEST)
    total+=j;
    }
    printf("Number of good decryption in total : %d/%d\n", total, VECTOR_SIZE*NBR_TEST);
#endif

}//end main()
