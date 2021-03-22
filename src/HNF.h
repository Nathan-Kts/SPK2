//
// Created by Nathan on 12/03/2021.
//

#ifndef TFE_KEM_HNF_H
#define TFE_KEM_HNF_H

void lll_reduce(double* b, int n, double lc, double uc);
void gram_schmidt(double* b, double* mu, double* B, int n);

#endif //TFE_KEM_HNF_H
