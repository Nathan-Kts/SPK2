project(TFE_KEM)

set(HEADER_FILES
        compute_intersection.h
        gaus_elimination.h
        lattice_functions.h
        math_functions.h
        other_functions.h
        parameters.h
        print_functions.h
        public_to_private.h
        crypto_functions.h
        sensor.h
        gateway.h
        random.h
        )

set(SOURCE_FILES
        compute_intersection.c
        gaus_elimination.c
        lattice_functions.c
        math_functions.c
        other_functions.c
        print_functions.c
        public_to_private.c
        crypto_functions.c
        sensor.c
        gateway.c
        random.c
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})