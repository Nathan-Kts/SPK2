#include "math_functions.h"

/**
 * @brief Function that performs Gauss-Elimination and returns the Upper triangular matrix
 * @param m number of vectors
 * @param n size of the vectors of the lattice
 * @param input the matrix to input
 */
void gauss_elimination(int m, int n, double input[m][n]){
    int i,j,k;
    for(i=0;i<m-1;i++){
        //Partial Pivoting
        for(k=i+1;k<m;k++){
            //If diagonal element(absolute value) is smaller than any of the terms below it
            if(fabs(input[i][i]) < fabs(input[k][i])){
                //Swap the rows
                for(j=0;j<n;j++){
                    double temp;
                    temp=input[i][j];
                    input[i][j]=input[k][j];
                    input[k][j]=temp;
                }
            }
        }
        //Begin Gauss Elimination
        for(k=i+1;k<m;k++){
            double  term= input[k][i] / input[i][i];
            for(j=0;j<n;j++){
                input[k][j]= input[k][j] - term * input[i][j];
            }
        }
    }
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            input[i][j] = modd(input[i][j], MODULO_LATTICE);
}
