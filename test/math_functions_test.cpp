#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/math_functions.c"

TEST_CASE("mod") {
    SUBCASE("modulo_positive_correct") {
        CHECK(mod(165, 64) == 37);
    }

    SUBCASE("modulo_negative_correct") {
        CHECK(mod(-8, 64) == 56);
    }
}

TEST_CASE("modd"){
    SUBCASE("modulo_positive_correct"){
        CHECK(modd(165.0, 64) == 37.0);
    }

    SUBCASE("modulo_negative_correct"){
        CHECK(modd(-8.0, 64) == 56.0);
    }
}

TEST_CASE("round"){
    SUBCASE("round_positive_down_correct"){
        CHECK(round(165.3) == 165.0);
    }

    SUBCASE("round_positive_up_correct"){
        CHECK(round(164.6) == 165.0);
    }

    SUBCASE("modulo_negative_down_correct"){
        CHECK(round(-8.7) == -9.0);
    }

    SUBCASE("modulo_negative_up_correct"){
        CHECK(round(-8.3) == -8.0);
    }
}

/*TEST_CASE("product_matrix_prime_matrix"){
    int nbr_vectors = 4;
    int vector_size = 4;
    double input[4][4] = {{23, 29, -4, 34}, {2, 654, 5, -453}, {23, 29, -4, 34}, {2, 654, 5, -453}};
    double output[4][4];
    double should_be[4][4] = {{1066, 3950, -164, -248},{3950, 857114, 6308, -590552},{-164, 6308, 82, -4802},{-248, -590552, -4802, 412730}};
    product_matrix_prime_matrix(nbr_vectors, vector_size, input, input, output);
    CHECK(output == should_be);
}*/
