//
// Created by Nathan on 14/05/2021.
//

#ifndef TFE_KEM_RANDOM_H
#define TFE_KEM_RANDOM_H

long shr3_seeded();
void r4_nor_setup();
float r4_uni();
float r4_nor();
double prepare_random();
double random_double(int maximum);

#endif //TFE_KEM_RANDOM_H
