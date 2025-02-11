//
// Created by Fuad Hasan on 2/10/25.
//

// Note: all tests are created using the python notebook: https://www.kaggle.com/code/fuadhasibulhasan/gaussiantest

#include "NumericalIntegrator.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Test Gaussian Integrator") {
    double tol = 1e-10;
    Polynomial x_cube({0, 0, 0, 1});
    Polynomial x_square({0, 0, 1});

    SECTION("X^3 for 4 points") {
        GaussLegendre gl4(4);
        printf("Integrating x^3 from -1 to 1 and the expected value is 0.0\n");
        REQUIRE_THAT(gl4.integrate(x_cube, -1.0, 1.0), Catch::Matchers::WithinRel(0, tol));

        printf("Integrating x^3 from 0 to 1 and the expected value is 0.25\n");
        REQUIRE_THAT(gl4.integrate(x_cube, 0.0, 1.0), Catch::Matchers::WithinRel(0.25, tol));

        printf("Integrating x^3 from -5 to 5 and the expected value is 0.0\n");
        REQUIRE_THAT(gl4.integrate(x_cube, -5.0, 5.0), Catch::Matchers::WithinRel(0, tol));

        printf("Integrating x^3 from -1 to 5 and the expected value is 156.0\n");
        REQUIRE_THAT(gl4.integrate(x_cube, -1.0, 5.0), Catch::Matchers::WithinRel(156.0, tol));
    }

    SECTION("X^3 for 1 point"){
        GaussLegendre gl1(1);

        printf("Integrating x^3 from -1 to 1 and the expected value is 0.0\n");
        REQUIRE_THAT(gl1.integrate(x_cube, -1.0, 1.0), Catch::Matchers::WithinRel(0, tol));

        printf("Integrating x^3 from -1 to 5 and the expected value is 48.0\n");
        REQUIRE_THAT(gl1.integrate(x_cube, -1.0, 5.0), Catch::Matchers::WithinRel(48.0, tol));
    }

    SECTION("X^3 for 3 points") {
        GaussLegendre gl3(3);

        printf("Integrating x^3 from -1 to 1 and the expected value is 0.0\n");
        REQUIRE_THAT(gl3.integrate(x_cube, -1.0, 1.0), Catch::Matchers::WithinRel(0, tol));

        printf("Integrating x^3 from -1 to 5 and the expected value is 156.0\n");
        REQUIRE_THAT(gl3.integrate(x_cube, -1.0, 5.0), Catch::Matchers::WithinRel(156.0, tol));
    }

    SECTION("X^2 for 4 points") {
        GaussLegendre gl4(4);
        double value = 0;

        value = gl4.integrate(x_square, -1.0, 1.0);
        printf("Integrating x^2 from -1 to 1 and the expected value is 2/3.0 and found %f\n", value);
        REQUIRE_THAT(value, Catch::Matchers::WithinRel(2./3., tol));

        value = gl4.integrate(x_square, 0.0, 1.0);
        printf("Integrating x^2 from 0 to 1 and the expected value is 1/3.0 and found %f\n", value);
        REQUIRE_THAT(value, Catch::Matchers::WithinRel(1./3., tol));

        value = gl4.integrate(x_square, -1.0, 5.0);
        printf("Integrating x^2 from -1 to 5 and the expected value is 42.0 and found %f\n", value);
        REQUIRE_THAT(value, Catch::Matchers::WithinRel(42.0, tol));
    }

    SECTION("Test Error Handling") {
        REQUIRE_THROWS(GaussLegendre(5));
        REQUIRE_THROWS(GaussLegendre(0));
        REQUIRE_THROWS(GaussLegendre(-1));
    }
}
