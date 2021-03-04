#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "../src/math_functions.c"

TEST_CASE("modulo_correct"){
    CHECK(mod(62, 64) == 63);
}