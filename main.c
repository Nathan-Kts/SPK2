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
//#include "src/HNF.c"
#include "quality.c"

//#define TEST
#define NBR_TEST 1000

int main()
{

    double test_1[3][3], test_2[3][3];
    double intersection[3][3];

    test_1[0][0] = 67;
    test_1[0][1] = -26;
    test_1[0][2] = -71;
    test_1[1][0] = 65;
    test_1[1][1] = -30;
    test_1[1][2] = -66;
    test_1[2][0] = -152;
    test_1[2][1] = 66;
    test_1[2][2] = 159;
    /*test_1[0][0] = 1; //Works in the case of a identity matrix
    test_1[0][1] = 0;
    test_1[0][2] = 0;
    test_1[1][0] = 0;
    test_1[1][1] = 1;
    test_1[1][2] = 0;
    test_1[2][0] = 0;
    test_1[2][1] = 0;
    test_1[2][2] = 1;*/
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            //test_1[i][j] = rand()%10+1;
            test_2[i][j] = test_1[i][j];
            intersection[i][j] = 0;
        }
    }
    /*printf("input\n");
    print_matrix(3, 3, test_1);
    inversion_matrix(3, test_1, intersection);
    printf("inverse\n");
    print_matrix(3, 3, intersection);*/
    /*printf("input\n");
    print_matrix(3, 3, test_1);
    intersection_lattice(3, 3, test_1, test_2, intersection);
    printf("output\n");
    print_matrix(3, 3, test_1);
    printf("output 2:\n");
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++)
            printf("%10.2f", intersection[i][j]);
        printf("\n");
    }
    printf("end 2:\n");*/


    //Gateway
    double private_lattice_g[NBR_VECTORS][VECTOR_SIZE], public_lattice_g[NBR_VECTORS][VECTOR_SIZE];
    gateway(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, public_lattice_g);

    //double test[NBR_VECTORS][VECTOR_SIZE];
    //gram_schimdt_modif(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, test);
    //print_matrix(NBR_VECTORS, VECTOR_SIZE, test);

    /*double lc = 1/4;
    double hc = 3/4;
    double temp2[VECTOR_SIZE*NBR_VECTORS];

    for (int i = 0; i < NBR_VECTORS; ++i) {
        for (int j = 0; j < VECTOR_SIZE; ++j) {
            temp2[VECTOR_SIZE*i+j] = private_lattice_g[i][j];
        }
    }*/

    //lll_reduce(temp2, VECTOR_SIZE, lc, hc);

    //Sensor 1 and 2
    double intersection_1[NBR_VECTORS][VECTOR_SIZE], intersection_2[NBR_VECTORS][VECTOR_SIZE];
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE], private_lattice_2[NBR_VECTORS][VECTOR_SIZE];

    sensor(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, private_lattice_1, intersection_1);
    sensor(NBR_VECTORS, VECTOR_SIZE, intersection_1, private_lattice_2, intersection_2);

    printf("Final intersection: \n");
    print_matrix(NBR_VECTORS, VECTOR_SIZE, intersection_2);

#if defined(TEST)
    int total = 0;
    for(int count = 0; count < NBR_TEST; count++){
        srand(count);
#endif

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
    product_matrix_vector(NBR_VECTORS, VECTOR_SIZE, intersection_2, secret, message);
    noise_maker(VECTOR_SIZE, message);
    printf("Broadcast Message : \n");
    print_vector(VECTOR_SIZE, message);


    //Decode
    double decode_0[VECTOR_SIZE], decode_1[VECTOR_SIZE], decode_2[VECTOR_SIZE];
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, message, decode_0);
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, message, decode_1);
    decode(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, message, decode_2);

    int j = 0;
    for (i = 0; i < VECTOR_SIZE; ++i) {
        if (decode_0[i] == decode_1[i])
            j++;
    }
    printf("Number of good decryption : %d/%d\n", j, VECTOR_SIZE);

#if defined(TEST)
    total+=j;
    }
    printf("Number of good decryption in total : %d/%d\n", total, VECTOR_SIZE*NBR_TEST);
#endif
    
}//end main()
