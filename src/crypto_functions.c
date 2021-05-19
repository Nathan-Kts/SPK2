#include "crypto_functions.h"
#include "math_functions.h"
#include "print_functions.h"
#include "gaus_elimination.h"
#include "random.h"

void decode(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]){
    product_matrix_vector(nbr_vectors, vector_size, private_lattice, message, decode);

    printf("Message decoded by 1 : \n");
    for (int i = 0; i < vector_size; ++i) {
        decode[i] = modd(decode[i], MODULO_LATTICE);
    }
    print_vector(vector_size, decode);

    decoding(vector_size, decode);
    print_vector(vector_size, decode);
}
void nearest_plane(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double message[vector_size], double decode[vector_size]){
    double gs[NBR_VECTORS][VECTOR_SIZE];
    for(int i = 0; i < nbr_vectors; i++)
        for(int j = 0; j < vector_size; j++)
            gs[i][j] = private_lattice[i][j];

    gram_schimdt(nbr_vectors, gs);
    double w[NBR_VECTORS][VECTOR_SIZE];
    double y[NBR_VECTORS][VECTOR_SIZE];
    double l;
    for (int i = 0; i < nbr_vectors; ++i) {
        w[nbr_vectors-1][i] = message[i];
    }
    for (int i = nbr_vectors-1; i > 0; i--) {
        l = product_vector_vector(nbr_vectors, vector_size, w, i, gs, i, nbr_vectors)/product_vector_vector(nbr_vectors, vector_size, gs, i, gs, i, nbr_vectors);
        for (int j = 0; j < nbr_vectors; ++j) {
            y[i][j] = (double) (int) l * private_lattice[i][j];
        }
        for (int j = 0; j < nbr_vectors; ++j) {
            w[i-1][j] = w[i][j] - (l - (double) (int) l)*gs[i][j] - ((double) (int) l)*private_lattice[i][j];
        }
    }

    for(int i = 0; i < nbr_vectors; i++)
        for(int j = 0; j < vector_size; j++)
            decode[i] = y[i][j];

    printf("Message decoded by 1 : \n");
    print_vector(vector_size, decode);
}
void decrypt(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size], double message[nbr_vectors], double decoded_message[nbr_vectors]){
    double temp_matrix[nbr_vectors][vector_size];
    double temp1[nbr_vectors], temp2[nbr_vectors];
    inversion_matrix(nbr_vectors, private_lattice, temp_matrix);
    product_matrix_vector(nbr_vectors, vector_size, temp_matrix, message, temp1);

    //printf("received messages after first product \n");
    //print_matrix(nbr_vectors, nbr_vectors, temp_matrix);
    //print_vector(nbr_vectors, decoded_message);

    /*for (int N = 0; N < VECTOR_SIZE; ++N) {
        decode_0[N] = round(decode_0[N]);
    }*/

    product_matrix_vector(nbr_vectors, vector_size, private_lattice, temp1, temp2);

    //printf("received messages after second \n");
    //print_vector(nbr_vectors, decoded_message);

    inversion_matrix(nbr_vectors, public_lattice, temp_matrix);
    product_matrix_vector(nbr_vectors, vector_size, temp_matrix, temp2, decoded_message);

    //printf("received messages after third \n");
    //print_vector(nbr_vectors, decoded_message);

    for (int N = 0; N < vector_size; N++) {
        decoded_message[N] = modd(decoded_message[N], MODULO_LATTICE);
    }

    printf("received messages \n");
    print_vector(nbr_vectors, decoded_message);
}

/**
 * @brief
 * @param message
 */
void decoding(int vector_size, double message[vector_size]){
    int i;
    for(i = 0; i < vector_size; i++) {
        if (message[i]<(MODULO_LATTICE/4) || message[i]>=(3*MODULO_LATTICE/4))
            message[i] = 1;
        else
            message[i] = 0;
    }
}

/**
 * @brief
 * @param message
 */
void noise_maker(int vector_size, double message[vector_size]){
    int i;
    double temp;
    for(i = 0; i < vector_size; i++) {
        message[i] += random_double(ERROR_MAX) - ERROR_MAX/2;
    }

}

void secret_builder(int nbr_vectors, int vector_size, double public_lattice[nbr_vectors][vector_size], double secret[nbr_vectors], double message[nbr_vectors]){
    int i;
    for (i = 0; i < nbr_vectors; ++i)
        secret[i] = (MODULO_LATTICE/2) * (random_double(1));


    printf("Secret Message : \n");
    print_vector(vector_size, secret);

    product_matrix_vector(nbr_vectors, vector_size, public_lattice, secret, message);

    //for(int j=0;j<VECTOR_SIZE;j++)
    //    message[j] = modd(message[j], MODULO_LATTICE);

    //printf("Broadcast Message without noise : \n");
    //print_vector(VECTOR_SIZE, message);

    noise_maker(vector_size, message);

    //printf("Broadcast Message with noise : \n");
    //print_vector(vector_size, message);
}

int count_good_decrypt(int nbr_vectors, double secret[nbr_vectors], double decoded_message[nbr_vectors]){
    int j = 0;
    double error = 0;
    //print_vector(nbr_vectors, secret);
    for (int i = 0; i < nbr_vectors; ++i) {
        //decoded_message[i] = modd(decoded_message[i], MODULO_LATTICE);
        if (secret[i] == 0 && decoded_message[i] <= MODULO_LATTICE/4){
            j++;
            error += abs(decoded_message[i]-secret[i]);
        }
        else if (secret[i] == 0 && decoded_message[i] >= 3*MODULO_LATTICE/4){
            j++;
            error += abs(MODULO_LATTICE-decoded_message[i]);
        }
        else if (secret[i] != 0 && decoded_message[i] > MODULO_LATTICE/4 && decoded_message[i] < 3*MODULO_LATTICE/4){
            j++;
            error += abs(decoded_message[i]-secret[i]);
        }
    }
    printf("Number of good decryption : %d/%d and error of %f\n", j, nbr_vectors, error);
    return j;
}

void decrypt_babai(int nbr_vectors, int vector_size, double private_lattice[nbr_vectors][vector_size], double public_lattice[nbr_vectors][vector_size], double message[nbr_vectors], double decoded_message[nbr_vectors]){
    double temp_matrix[nbr_vectors][vector_size];
    double temp1[nbr_vectors], temp2[nbr_vectors];
    double s[vector_size];
    double c;

    for (int i = 0; i < vector_size; ++i) {
        s[i] = message[i];
    }

    for (int i = 0; i < nbr_vectors; ++i) {
        for (int j = 0; j < vector_size; ++j) {
            temp_matrix[i][j] = private_lattice[i][j];
        }
    }

    gauss_elimination(nbr_vectors, vector_size, temp_matrix);

    for (int i = vector_size-1; i >= 0; i--) {
        c = round(product_vector_alone_vector(nbr_vectors, vector_size, s, temp_matrix, i, nbr_vectors)/product_vector_vector(nbr_vectors, vector_size, temp_matrix, i, temp_matrix, i, nbr_vectors));
        //printf("c = %f\n", product_vector_alone_vector(nbr_vectors, vector_size, s, temp_matrix, i, nbr_vectors));
        //printf("c_len = %f\n", product_vector_vector(nbr_vectors, vector_size, temp_matrix, i, temp_matrix, i, nbr_vectors));
        for (int j = 0; j < vector_size; j++) {
            s[j] -= c * private_lattice[i][j];
            //printf("c<2 = %f %f %f\n", c, private_lattice[i][j], c * private_lattice[i][j]);
            //print_matrix(nbr_vectors, vector_size, private_lattice);
        }
        //print_vector(vector_size, s);
    }

    for (int i = 0; i < vector_size; ++i) {
        temp1[i] = message[i]-s[i];
    }

    inversion_matrix(nbr_vectors, public_lattice, temp_matrix);
    product_matrix_vector(nbr_vectors, vector_size, temp_matrix, temp1, decoded_message);


    for (int N = 0; N < vector_size; N++) {
        decoded_message[N] = modd(decoded_message[N], MODULO_LATTICE);
    }

    printf("received messages \n");
    print_vector(nbr_vectors, decoded_message);
}