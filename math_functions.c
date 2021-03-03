#include "math_functions.h"
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
#include "gaus_elimination.h"

double exp(double input){
    return (double) powf((float) 2.71828, (float) input);
}

int msb(int n){
    int i = 0;
    for (; n; n >>= 1, i++)
        ; /* empty */
    return i;
}

long mod(long a, long b){
    long output = a % b;
    if(output < 0)
        output+=b;
    return output;
}//end mod()

double log(double y){
    int log2;
    double divisor, x, result;

    log2 = msb((int)y); // See: https://stackoverflow.com/a/4970859/6630230
    divisor = (double)(1 << log2);
    x = y / divisor;    // normalized value between [1.0, 2.0]

    result = -1.7417939 + (2.8212026 + (-1.4699568 + (0.44717955 - 0.056570851 * x) * x) * x) * x;
    result += ((double)log2) * 0.69314718; // ln(2) = 0.69314718

    return result;
}

double round(double input){
    if (input >= 0.0)
        input += 0.5;
    else
        input -= 0.5;
    return (int) input;
}


double product_vector_vector(double a[VECTOR_SIZE][VECTOR_SIZE], int aa, double b[VECTOR_SIZE][VECTOR_SIZE], int bb, int size){
    int i;
    double output = 0;
    for(i = 0; i < size; i++)
        output += a[i][aa]*b[i][bb];
    return output;
}

void product_matrix_prime_matrix(double input1[VECTOR_SIZE][VECTOR_SIZE], double input2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j, k;
    for(i = 0; i < VECTOR_SIZE; i++){
        for(j = 0; j < VECTOR_SIZE; j++){
            output[i][j] = 0;
            for(k = 0; k < VECTOR_SIZE; k++)
                output[i][j] += input1[k][i] * input2[k][j];
        }
    }
}

void product_matrix_matrix(double input1[VECTOR_SIZE][VECTOR_SIZE], double input2[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j, k;
    for(i = 0; i < VECTOR_SIZE; i++)
    {
        for( j = 0; j < VECTOR_SIZE; j++)
        {
            output[i][j]=0;
            for(k = 0; k < VECTOR_SIZE; k++)
                output[i][j]+=input1[i][k]*input2[k][j];
        }
    }
}

void inversion_matrix(double matrix[VECTOR_SIZE][VECTOR_SIZE], double output[VECTOR_SIZE][VECTOR_SIZE]){
    int i, j, k;
    double ratio, temp;
    //creation of identity matrix
    for (i = 0; i < VECTOR_SIZE; i++)
        for (j = 0; j < VECTOR_SIZE; j++)
            if (i == j)
                output[i][j] = 1;
            else
                output[i][j] = 0;


    // Applying Gauss Jordan Elimination
    for (k = 0;
         k < VECTOR_SIZE; k++)                                  //by some row operations,and the same row operations of
    {                                                       //Unit mat. I gives the inverse of matrix A
        temp = matrix[k][k];                   //'temp'
        // stores the A[k][k] value so that A[k][k]  will not change
        for (j = 0; j < VECTOR_SIZE; j++)      //during the operation //A[i] //[j]/=A[k][k]  when i=j=k
        {
            matrix[k][j] /= temp;                                  //it performs // the following row operations to make A to unit matrix
            output[k][j] /= temp;                                  //R0=R0/A[0][0],similarly for I also
        }                                                   //R1=R1-R0*A[1][0] similarly for I
        for (i = 0; i < VECTOR_SIZE; i++)                              //R2=R2-R0*A[2][0]      ,,
        {
            temp = matrix[i][k];                       //R1=R1/A[1][1]
            for (j = 0; j < VECTOR_SIZE; j++)             //R0=R0-R1*A[0][1]
            {                                   //R2=R2-R1*A[2][1]
                if (i == k)
                    break;                      //R2=R2/A[2][2]
                matrix[i][j] -= matrix[k][j] * temp;          //R0=R0-R2*A[0][2]
                output[i][j] -= output[k][j] * temp;          //R1=R1-R2*A[1][2]
            }
        }
    }
}