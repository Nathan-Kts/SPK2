#pragma once

#define HADAMARD_RATIO 0.15
#define NBR_VECTORS 10
#define VECTOR_SIZE NBR_VECTORS
#define DATA_PER_PACKET 38
#define MODULO_LATTICE 1289 //12289 //Max 2^16-1 = 65.535
#define PRIVATE_LATTICE_LIMIT MODULO_LATTICE/2
#define PUBLIC_LATTICE_LIMIT 20
#define ERROR_MAX 1

//#define PRINT_MATRICES
#define TEST
#define NBR_TEST 1000

#define N_inv 12265
#define UDP_CLIENT_PORT	8765
#define UDP_SERVER_PORT	5678
#define UDP_EXAMPLE_ID  190

# include <math.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>

struct lattice_metadata {
	    char id;
	    unsigned int dim_n;
            unsigned int dim_m;
            unsigned int max;
        };

struct lattice {
            int vectors[VECTOR_SIZE];
	    struct lattice_metadata metadata;
        };

struct udp_lattice {
            int vectors[DATA_PER_PACKET];
	    struct lattice_metadata metadata;
        };

//For the sensor
#define START_TIME		(4 * CLOCK_SECOND) //time after which he start asking the lattice
#define MAX_RECHECK_TIME	(10 * CLOCK_SECOND)
//#define MAX_PAYLOAD_LEN		2

struct point {
            int vector[VECTOR_SIZE];
            long point[VECTOR_SIZE];
        };
