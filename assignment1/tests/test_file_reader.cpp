//
// Created by Fuad Hasan on 2/11/25.
//

#include "read_integration_setup.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Test file reader") {
    PolynomialIntegrator polyInt = readPolynomial("assets/x3_gauss_-1to5.txt");
    double integral = polyInt.integrator->integrate(polyInt.polynomial, polyInt.lowerBound, polyInt.upperBound);

    printf("\n=========> Integrating <=========\n");
    printf("Integral: %f\n", integral);
    printf("=================================\n");

    REQUIRE_THAT(integral, Catch::Matchers::WithinAbs(156.0, 1e-10));
}