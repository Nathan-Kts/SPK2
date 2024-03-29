#pragma once

#include <stdio.h>
#include <math.h> 

/* Find an orthonormal basis for the set of vectors q 
* using the Gram-Schmidt Orthogonalization process
void gram_schimdt_modif(double A[VECTOR_SIZE][VECTOR_SIZE], double Q[VECTOR_SIZE][VECTOR_SIZE]) { 
	int i, j, k;
	double A0[VECTOR_SIZE][VECTOR_SIZE];
	double temp;

    	for (i = 0; i < VECTOR_SIZE; i++){
            for (j = 0; j < VECTOR_SIZE; j++) {
                 A0[i][j] = A[i][j];
            }
	    printf("\n");
        }

	for(i=0; i<VECTOR_SIZE; ++i) {  
	    // Normalisation ok column i
	    double scaling_factor = 0;
	    for(j=0; j<VECTOR_SIZE; ++j) 
		scaling_factor += A0[j][i]*A0[j][i];
	    scaling_factor = sqrt(scaling_factor);
	    for(j=0; j<VECTOR_SIZE; ++j)
		Q[j][i] = A0[j][i]/scaling_factor;

	    //Orthogonalization of all the other columns
	    for(k=i+1; k<VECTOR_SIZE; k++){ 
                temp = product_vector_vector(A0, k, Q, i, VECTOR_SIZE);
		//printf("%d\n", (int) (1000*temp));
		for(j=0; j<VECTOR_SIZE; j++){
		    A0[j][k] = A0[j][k] - Q[j][i]*temp;
		}
	    }
	}
	product_matrix_prime_matrix(Q, A, VECTOR_SIZE, A0);
    	for (i = 0; i < VECTOR_SIZE; i++){
            for (j = 0; j < VECTOR_SIZE; j++) {
                 Q[i][j] = A0[i][j];
            }
	    printf("\n");
        }
} 

*/











/*===============================================================================================

The LLL-Reduction Algorithm

Authors:
--------

*Grady Williams (gradyrw@gmail.com)

================================================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "../src/math_functions.c"


//Numerically stable gram schmidt algorithm
void gram_schmidt(double* b, double* mu, double* B, int n)
{
    int i,j,k;
    double* b_star;
    b_star = (double*)malloc(n*n*sizeof(double));
    for (i = 0; i < n; i++){
        //b*_i = b_i
        for (j = 0; j < n; j++){
            b_star[j*n + i] = b[j*n + i];
        }
        //Initialize a term to keep track of the summation term
        //in the gram schmidt algorithm
        double* summand;
        summand = (double*)malloc(n*sizeof(double));
        for (j = 0; j < n; j++){
            summand[j] = 0;
        }
        //Calculate mu_ij and summand value
        for (j = 0; j < i; j++){
            //mu_ij = <b_i, b*_j>/<b*_j, b*_j>
            double numerator_mu = 0;
            for (k = 0; k < n; k++){
                numerator_mu += b[k*n + i]*b_star[k*n + j];
            }
            mu[i*n + j] = numerator_mu/B[j];
            for (k = 0; k < n; k++){
                summand[k] += mu[i*n + j]*b_star[k*n + j];
            }
        }
        //Calculate new b_star values and B values
        for (j = 0; j < n; j++){
            b_star[j*n + i] -= summand[j];
        }
        double dot = 0;
        for (j = 0; j < n; j++){
            dot += b_star[j*n + i]*b_star[j*n + i];
        }
        B[i] = dot;
    }
}



/*
Performs Lenstra-Lenstra-Lovasv reduction on a given lattive n in 
n-dimensional real space. The lc and  uc are the upper and lower constants 
used in the LLL-Algorithm. The default is lc = 1/2 and uc = 3/4. We 
presume that our algorithm has been given a matrix represented in an 
array with standard C ordering. Reduction is performed on the columns of b.*/

void lll_reduce(double* b, int n, double lc, double uc)
{
    //Performs the Gramm-Schmidt Algorithm
    double* mu;
    double* B;
    mu = (double*)malloc(n*n*sizeof(double));
    B = (double*)malloc(n*sizeof(double));

    gram_schmidt(b,mu, B, n);
    printf("GS fait\n");
    int k = 1;
    int i,l;
    while (k < n){
        printf("Start %d\n", k);
        //Step 1 of LLL, achieve m_(k,k-1) <= lc
        //This is condition (1.18) from LLL
        if (fabs(mu[k*n + k - 1]) > lc) {
            int r = round(mu[k*n + k - 1]);
            //replace b_k by b_k - r*b_(k-1)
            for (i = 0; i < n; i++){
                b[k + i*n] = b[k + i*n] - r*b[k-1 + i*n];
            }
            //Change the mu's accordingly
            for (i = 0; i < k-1; i++) {
                mu[k*n + i] = mu[k*n + i] - r*mu[(k-1)*n + i];
            }
            mu[k*n + k-1] = mu[k*n + k-1] - r;
        }
        printf("suite... 0\n");
        //This completes step one of the algorithm
        //Step 2
        //Case 1: B_k + (mu(k,k-1)^2)B_(k-1) < uc*B_(k-1)
        if ((B[k] + mu[k*n + k -1]*mu[k*n + k -1]*B[k-1] < uc*B[k-1]) && (k > 0)){
            printf("suite...\n");
            //First swap b_k and b_(k-1)
            for (i = 0; i < n; i++) {
                double temp = b[i*n + k];
                b[i*n + k] = b[i*n + k-1];
                b[i*n + k-1] = temp;
            }
            printf("suite... 2\n");

            //We need to save three values for the rest of Step 2 case 1, these
            //are B_k, B_k + mu_(k,k-1)*B[k-1], and mu_(k,k-1)
            double B_temp = B[k];
            double C = B[k] + mu[k*n + k-1]*mu[k*n + k-1]*B[k-1];
            double mu_temp = mu[k*n + k-1];
            //Now we continue with the algorithm, first adjust B
            mu[k*n + k-1] = mu_temp*B[k-1]/C;
            B[k] = B[k-1]*B[k]/C;
            B[k-1] = C;
            //All other B values stay the same
            //Next we adjust mu
            for (i = k+1; i < n; i++){
                double temp = mu[i*n + k-1];
                mu[i*n + k-1] = mu[i*n + k-1]*mu[k*n + k-1] + mu[i*n + k]*B_temp/C;
                mu[i*n + k] = temp - mu[i*n + k]*mu_temp;
            }
            printf("suite...3\n");

            for (i = 0; i < k-1; i++){
                double temp = mu[(k-1)*n + i];
                mu[(k-1)*n + i] = mu[k*n + i];
                mu[k*n + i] = temp;
            }
            printf("suite...4\n");

            //All other mu values stay the same.
            //Decrement k
            k = k-1;
            printf("if %d\n", k);
            //This concludes step 2 case 1
        } //Case 2: B_k + (mu(k,k-1)^2)B_(k-1) >= uc*B_(k-1) or k == 0
        else {
            l = k;
            printf("suite... -1\n");
            while (l > 0) {
                printf("suite... -2 %d\n", l);
                l = l-1;
                if (fabs(mu[k*n + l]) > lc) {
                    int r = round(mu[k*n + l]);
                    //b_k = b_k - r*b_l
                    for (i = 0; i < n; i++) {
                        b[i*n + k] = b[i*n + k] - r*b[i*n + l];
                    }
                    for (i = 0; i < l; i++) {
                        mu[k*n + i] = mu[k*n + i] - r*mu[l*n + i];
                    }
                    mu[k*n + l] = mu[k*n + l] - r;
                    //The other mu are unchanged
                    l = k;
                }
            }
            k = k + 1;
            printf("end %d\n", k);
        }
    }
}