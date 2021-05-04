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

#define TEST
#define NBR_TEST 1000

int main()
{

#if defined(TEST)
    int total = 0;
    for(int count = 0; count < NBR_TEST; count++){
        srand(count);
#endif

    //Gateway
    double private_lattice_g[NBR_VECTORS][VECTOR_SIZE], public_lattice_g[NBR_VECTORS][VECTOR_SIZE];
    gateway(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, public_lattice_g);

    printf("Private g\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_g);
    printf("Public g\n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, public_lattice_g);


    //Sensor 1 and 2
    double intersection_1[NBR_VECTORS][VECTOR_SIZE], intersection_2[NBR_VECTORS][VECTOR_SIZE];
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE];//, private_lattice_2[NBR_VECTORS][VECTOR_SIZE];

    //sensor(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, private_lattice_1, intersection_1);
    //sensor(NBR_VECTORS, VECTOR_SIZE, intersection_1, private_lattice_2, intersection_2);

    //printf("Final intersection used to encrypt : \n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_1);

    //printf("Private 1\n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, private_lattice_1);
    //printf("Public 1\n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_1);

    int i;
    double secret[VECTOR_SIZE];
    for (i = 0; i < VECTOR_SIZE; ++i)
        secret[i] = (MODULO_LATTICE) * (rand() % 2);
    /*if(i%2==0)
        secret[i]=0;
    else
        secret[i]= MODULO_LATTICE/2;*/

    double message[VECTOR_SIZE];
    printf("Secret Message : \n");
    print_vector(VECTOR_SIZE, secret);

    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, secret, message);
    noise_maker(VECTOR_SIZE, message);
    printf("Broadcast Message : \n");
    print_vector(VECTOR_SIZE, message);


    //Decode
    double decode_0[VECTOR_SIZE], decode_1[VECTOR_SIZE];//, decode_2[VECTOR_SIZE];


    //nearest_plane(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, message, decode_0);

    //decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, message, decode_1);
    //decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, message, decode_2);


    double output[NBR_VECTORS][VECTOR_SIZE];




    inversion_matrix(NBR_VECTORS, private_lattice_g, output);
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, output, message, decode_0);

    /*for (int N = 0; N < VECTOR_SIZE; ++N) {
        decode_0[N] = round(decode_0[N]);
    }*/

    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, decode_0, decode_1);

    inversion_matrix(NBR_VECTORS, public_lattice_g, output);
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, output, decode_1, decode_0);

    /*for (int N = 0; N < VECTOR_SIZE; ++N) {
        decode_0[N] = round(decode_0[N]);
    }*/

    printf("received messages \n");
    print_vector(NBR_VECTORS, decode_0);
    //printf("test\n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);


    int j = 0;
    for (i = 0; i < VECTOR_SIZE; ++i) {
        if (decode_0[i] <= MODULO_LATTICE/2 && secret[i] == 0)
            j++;
        if (secret[i] == MODULO_LATTICE && decode_0[i] > MODULO_LATTICE/2)
            j++;
    }
    printf("Number of good decryption : %d/%d\n", j, VECTOR_SIZE);



/*

    inversion_matrix(NBR_VECTORS, private_lattice_1, output);
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, output, message, decode_0);
    for (int N = 0; N < VECTOR_SIZE; ++N) {
        decode_0[N] = round(decode_0[N]);
    }
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, decode_0, decode_1);

    inversion_matrix(NBR_VECTORS, intersection_1, output);
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, output, decode_1, decode_0);

    for (int N = 0; N < VECTOR_SIZE; ++N) {
        decode_0[N] = round(decode_0[N]);
    }

    printf("received messages \n");
    print_vector(NBR_VECTORS, decode_0);
    //printf("test\n");
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, output);






    for (i = 0; i < VECTOR_SIZE; ++i) {
        if (secret[i] == 50 && decode_0[i] >= 20)
            j++;
        if (secret[i] == 0 && decode_0[i] <= 20)
            j++;
    }
    printf("Number of good decryption : %d/%d\n", j, 2*VECTOR_SIZE);
*/

    double temp[NBR_VECTORS][VECTOR_SIZE];
    printf("Length of private lattice g : %f and the public : %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, temp), gs_norm(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, temp));
    //printf("Length of private lattice 1 : %f and the public : %f\n", gs_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, temp), gs_norm(NBR_VECTORS, VECTOR_SIZE, intersection_1, temp));
    //printf("Length of private lattice 2 : %f - %f and the public : %f - %f\n", gram_schimdt_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, intersection_2), max_norm(NBR_VECTORS, VECTOR_SIZE, private_lattice_2), gram_schimdt_norm(NBR_VECTORS, VECTOR_SIZE, intersection_2, intersection_2), max_norm(NBR_VECTORS, VECTOR_SIZE, intersection_2));

#if defined(TEST)
    total+=j;
    }
    printf("Number of good decryption in total : %d/%d\n", total, VECTOR_SIZE*NBR_TEST);
#endif

}//end main()
