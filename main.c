#include <stdio.h>
#include <crypto_functions.h>
#include <sensor.h>
#include <gateway.h>
#include <random.h>
#include <time.h>

#include "src/parameters.h"
#include "src/math_functions.c"
#include "src/lattice_functions.c"
#include "src/print_functions.c"
#include "src/public_to_private.c"
#include "src/compute_intersection.c"
#include "quality.c"

void sleep(int nbr_vectors){
    int y = 0;
    for (int i = 0; i < nbr_vectors*nbr_vectors; ++i) {
        y = 2 + 2;
    }
    printf("\n");
}

int main()
{
    printf("Building random generator\n");
    prepare_random();

    int total_1 = 0;
    int total_2 = 0;
    int total_3 = 0;
    int total_pirate = 0;
    int total_g = 0;
#if defined(TEST)
    for(int count = 0; count < NBR_TEST; count++){
        srand(count);
#endif

    clock_t start_time = clock();
    /// Gateway
    double private_lattice_g[NBR_VECTORS][VECTOR_SIZE], public_lattice_g[NBR_VECTORS][VECTOR_SIZE];
    gateway(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, public_lattice_g);

    double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
    printf("Done in %f seconds\n", elapsed_time);

    sleep(NBR_VECTORS);

    /// Sensor 1 and 2
    //double intersection_3[NBR_VECTORS][VECTOR_SIZE], intersection_2[NBR_VECTORS][VECTOR_SIZE];
    double intersection_1[NBR_VECTORS][VECTOR_SIZE];
    //double private_lattice_3[NBR_VECTORS][VECTOR_SIZE], private_lattice_2[NBR_VECTORS][VECTOR_SIZE];
    double private_lattice_1[NBR_VECTORS][VECTOR_SIZE];

    sensor(NBR_VECTORS, VECTOR_SIZE, public_lattice_g, private_lattice_1, intersection_1);

    //sensor(NBR_VECTORS, VECTOR_SIZE, intersection_1, private_lattice_2, intersection_2);

    //sensor(NBR_VECTORS, VECTOR_SIZE, intersection_2, private_lattice_3, intersection_3);


    /// Message creator (encryption)
    double message[NBR_VECTORS], secret[NBR_VECTORS];
    secret_builder(NBR_VECTORS, VECTOR_SIZE, intersection_1, secret, message);

    printf("Message :\n");
    print_vector(NBR_VECTORS, message);

    /// Decoding
    double decoded_0[VECTOR_SIZE], decoded_1[VECTOR_SIZE];
    double decoded_2[VECTOR_SIZE], decoded_3[VECTOR_SIZE];
    double decoded_pirate[VECTOR_SIZE];

    decrypt_babai(NBR_VECTORS, VECTOR_SIZE, private_lattice_g, intersection_1, message, decoded_0);
    total_g = total_g + count_good_decrypt(NBR_VECTORS, secret, decoded_0);

    decrypt_babai(NBR_VECTORS, VECTOR_SIZE, private_lattice_1, intersection_1, message, decoded_1);
    total_1 = total_1 + count_good_decrypt(NBR_VECTORS, secret, decoded_1);

    /*decrypt_babai(NBR_VECTORS, VECTOR_SIZE, private_lattice_2, intersection_3, message, decoded_2);
    total_2 = total_2 + count_good_decrypt(NBR_VECTORS, secret, decoded_2);

    decrypt_babai(NBR_VECTORS, VECTOR_SIZE, private_lattice_3, intersection_3, message, decoded_3);
    total_3 = total_3 + count_good_decrypt(NBR_VECTORS, secret, decoded_3);

    decrypt_babai(NBR_VECTORS, VECTOR_SIZE, intersection_3, intersection_3, message, decoded_pirate);
    total_pirate = total_pirate + count_good_decrypt(NBR_VECTORS, secret, decoded_pirate);*/

    print_final_output(NBR_VECTORS, secret, decoded_0, decoded_1);
    //print_final_output_long(NBR_VECTORS, secret, decoded_0, decoded_1, decoded_2, decoded_3, decoded_pirate);

#if defined(TEST)
    }
    printf("Number of good decryption in base lattice : %d/%d\n", total_g, VECTOR_SIZE*NBR_TEST);
    printf("Number of good decryption in sensor 1 : %d/%d\n", total_1, VECTOR_SIZE*NBR_TEST);
    //printf("Number of good decryption in sensor 2 : %d/%d\n", total_2, VECTOR_SIZE*NBR_TEST);
    //printf("Number of good decryption in sensor 3 : %d/%d\n", total_3, VECTOR_SIZE*NBR_TEST);
    //printf("Number of good decryption in sensor pirate : %d/%d\n", total_pirate, VECTOR_SIZE*NBR_TEST);
#endif

}//end main()
