#include "math_functions.h"
#include "print_functions.h"

/**
 * @brief Computes the natural exponential of the input
 * @param input
 * @return The natural exponential
 */
double exp(double input){
    return (double) powf((float) 2.71828, (float) input);
}

/**
 * @brief Computes the modulus of input (input is a "long")
 * @warning It does this as Matlab not as C. All the negatives ]-b, 0[ are brought back to the positives [0, b[
 * @param a The "long integer" to compute
 * @param b The divisor
 * @return The computed number
 */
long mod(long a, int b){
    long output = a % b;
    if(output < 0)
        output+=b;
    return output;
}//end mod()

/**
 * @brief Computes the modulus of a "double"
 * @param a The "double" to compute
 * @param b The divisor
 * @return The modulus rounded to the nearest integer
 */
double modd(double a, int b){
    if(a >= -0.01) //TODO to adjust with time
        return (double) ((int) (a+0.5) % b);
    else
        return (double) ((int) (a-0.5) % b) + b;
}//end modd()

/**
 * @brief
 * @param n
 * @return
 */
int msb(int n){
    int i = 0;
    for (; n; n >>= 1, i++)
        ; /* empty */
    return i;
}

/**
 * @brief Computes the natural logarithm of input
 * @param input
 * @return The natural logarithm of input
 */
double log(double input){
    int log2;
    double divisor, x, result;

    log2 = msb((int)input); // See: https://stackoverflow.com/a/4970859/6630230
    divisor = (double)(1 << log2);
    x = input / divisor;    // normalized value between [1.0, 2.0]

    result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
    result += ((double)log2) * 0.69314718; // ln(2) = 0.69314718

    return result;
}

/**
 * @brief round a double to the nearest integer
 * @param input
 * @return The rounded integer as a "double"
 */
double round(double input){
    if (input >= 0.0)
        input += 0.5;
    else
        input -= 0.5;
    return (double) ((int) input);
}

/**
 * @brief Computes the product of two vectors within matrices
 * @warning The vectors of course have to the same size
 * @param nbr_vectors Number of vectors in the lattice
 * @param vector_size Size of the vectors in the lattice
 * @param vector_1 The matrix containing the first vector
 * @param line_1 The index of the vector_1
 * @param vector_2 The matrix containing the second vector
 * @param line_2 The index of the vector_2
 * @param size The size of the matrices
 * @return
 */
double product_vector_vector(int nbr_vectors, int vector_size, double vector_1[nbr_vectors][vector_size], int line_1, double vector_2[nbr_vectors][vector_size], int line_2, int size){
    int i;
    double output = 0;
    for(i = 0; i < size; i++)
        output += vector_1[i][line_1] * vector_2[i][line_2];
    return output;
}

/**
 * @brief Computes the product of a transposed matrix by another matrix
 * @param matrix_1 The matrix to transpose
 * @param matrix_2 The second matrix
 * @param output The product of the matrices
 */
void product_matrix_prime_matrix(int nbr_vectors, int vector_size, double matrix_1[nbr_vectors][vector_size], double matrix_2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]){
    int i, j, k;
    for(i = 0; i < vector_size; i++){ //TODO Not shure to verify that is is vector_size
        for(j = 0; j < vector_size; j++){
            output[i][j] = 0;
            for(k = 0; k < nbr_vectors; k++)
                output[i][j] += matrix_1[k][i] * matrix_2[k][j];
            //output[i][j] = modd(output[i][j], MODULO_LATTICE);
        }
    }
    //printf("Exit\n");
    //print_matrix(nbr_vectors, vector_size, matrix_1);
}

/**
 * @brief Computes the product of two matrices
 * @param matrix_1 The first matrix
 * @param matrix_2 The second matrix
 * @param output The product of the matrices
 */
void product_matrix_matrix(int nbr_vectors, int vector_size, double matrix_1[nbr_vectors][vector_size], double matrix_2[nbr_vectors][vector_size], double output[nbr_vectors][vector_size]){
    int i, j, k;
    for(i = 0; i < vector_size; i++)
    {
        for( j = 0; j < nbr_vectors; j++)
        {
            output[i][j]=0;
            for(k = 0; k < vector_size; k++)
                output[i][j]+= matrix_1[i][k] * matrix_2[k][j];
            //output[i][j] = modd(output[i][j], MODULO_LATTICE);
        }
    }
}

/**
 * @brief Computes the product of a matrices by a vector
 * @param matrix The matrix
 * @param vector The vector
 * @param output
 */
void product_matrix_vector(int nbr_vectors, int vector_size, double matrix[nbr_vectors][vector_size], double vector[vector_size], double output[vector_size]){
    int i, j, k;
    for(i = 0; i < nbr_vectors; i++)
    {
        output[i] = 0;
        for(j = 0; j < vector_size; j++)
        {
            output[i]+=matrix[i][j]*vector[j];
        }
        //output[i] = modd(output[i], MODULO_LATTICE);
    }
}

/**
 * @brief Inverses a square matrix with Gauss Jordan Elimination
 * @warning Matrix has to be square to invert
 * @param matrix Matrix to inverse
 * @param output The inverse of the matrix
 */
void inversion_matrix(int vector_size, double matrix[vector_size][vector_size], double output[vector_size][vector_size]){
    int i, j, k;
    double temp;
    double compute_matrix[vector_size][vector_size];
    for (i = 0; i < vector_size; i++)
        for (j = 0; j < vector_size; j++)
            compute_matrix[i][j] = matrix[i][j];

    //creation of identity matrix
    for (i = 0; i < vector_size; i++)
        for (j = 0; j < vector_size; j++)
            if (i == j)
                output[i][j] = 1;
            else
                output[i][j] = 0;


    // Applying Gauss Jordan Elimination
    for (k = 0;
         k < vector_size; k++)                                  //by some row operations,and the same row operations of
    {                                                       //Unit mat. I gives the inverse of matrix A
        temp = compute_matrix[k][k];                   //'temp'
        // stores the A[k][k] value so that A[k][k]  will not change
        for (j = 0; j < vector_size; j++)      //during the operation //A[i] //[j]/=A[k][k]  when i=j=k
        {
            compute_matrix[k][j] /= temp;                                  //it performs // the following row operations to make A to unit matrix
            output[k][j] /= temp;                                  //R0=R0/A[0][0],similarly for I also
        }                                                   //R1=R1-R0*A[1][0] similarly for I
        for (i = 0; i < vector_size; i++)                              //R2=R2-R0*A[2][0]      ,,
        {
            temp = compute_matrix[i][k];                       //R1=R1/A[1][1]
            for (j = 0; j < vector_size; j++)             //R0=R0-R1*A[0][1]
            {                                   //R2=R2-R1*A[2][1]
                if (i == k)
                    break;                      //R2=R2/A[2][2]
                compute_matrix[i][j] -= compute_matrix[k][j] * temp;          //R0=R0-R2*A[0][2]
                output[i][j] -= output[k][j] * temp;          //R1=R1-R2*A[1][2]
            }
        }
    }
}