//
// Created by Fuad Hasan on 2/10/25.
//

// Note: all tests are created using the python notebook: https://www.kaggle.com/code/fuadhasibulhasan/gaussiantest

#include "NumericalIntegrator.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include <cmath>

TEST_CASE("Test Gaussian Quadrature") {
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

TEST_CASE("Test Chebyshev Quadrature") {
    double tol = 1e-10;
    Polynomial x_cube({0, 0, 0, 1});

    SECTION("ChebyShev First Kind"){
        auto cb5 = Chebychev(5, ChebyshevType::FIRST_KIND);
        double value = 0.0;

        SECTION("Check Points"){
            auto points = cb5.getChebychevPoints();
            REQUIRE(points.size() == 5);

            REQUIRE_THAT(points[0], Catch::Matchers::WithinRel(cos(M_PI/10), tol));
            REQUIRE_THAT(points[1], Catch::Matchers::WithinRel(cos(3*M_PI/10), tol));
            REQUIRE_THAT(points[2], Catch::Matchers::WithinRel(cos(5*M_PI/10), tol));
            REQUIRE_THAT(points[3], Catch::Matchers::WithinRel(cos(7*M_PI/10), tol));
            REQUIRE_THAT(points[4], Catch::Matchers::WithinRel(cos(9*M_PI/10), tol));
        }

        SECTION("Check Weights"){
            auto weights = cb5.getChebychevWeights();
            REQUIRE(weights.size() == 5);

            for (int i = 0; i < 5; i++){
                REQUIRE_THAT(weights[i], Catch::Matchers::WithinRel(M_PI/5, tol));
            }
        }

        SECTION("X^3 Check Interpolation"){
            value = cb5.integrate(x_cube, -1.0, 1.0);
            printf("Integrating x^3 from -1 to 1 and the expected value is 0.0 and found %f\n", value);
            REQUIRE_THAT(value+1.0, Catch::Matchers::WithinRel(0.0+1.0, tol)); // comparing 0 isn't working
        }

        SECTION("X^2 Check Interpolation"){
            Polynomial x_square({0, 0, 1});
            auto cb10 = Chebychev(10, ChebyshevType::FIRST_KIND);
            value = cb10.integrate(x_square, -1.0, 1.0);
            printf("Integrating chebychev x^2 from -1 to 1 and the expected value is 1.570796326794678 and found %f\n", value);
            REQUIRE_THAT(value, Catch::Matchers::WithinRel(1.570796326794678, tol));
        }
    }

    SECTION("Chebyshev Second Kind"){
        auto cb10 = Chebychev(10, ChebyshevType::SECOND_KIND);
        Polynomial x_square({0, 0, 1});
        double value = 0.0;

        SECTION("Check Points"){
            auto points = cb10.getChebychevPoints();
            REQUIRE(points.size() == 10);

            for (int i = 0; i < 10; i++) {
                REQUIRE_THAT(points[i], Catch::Matchers::WithinRel(cos((i + 1) * M_PI / 11), tol));
            }
        }

        SECTION("Check Weights"){
            auto weights = cb10.getChebychevWeights();
            REQUIRE(weights.size() == 10);

            for (int i = 0; i < 10; i++){
                REQUIRE_THAT(weights[i], Catch::Matchers::WithinRel(M_PI/11 * pow(sin((i+1)*M_PI/11), 2), tol));
            }
        }

        SECTION("X^3 Check Interpolation"){
            value = cb10.integrate(x_cube, -1.0, 1.0);
            printf("Integrating chebychev x^3 from -1 to 1 and the expected value is 0.0 and found %f\n", value);
            REQUIRE_THAT(value+1.0, Catch::Matchers::WithinRel(0.0+1.0, tol)); // comparing 0 isn't working
        }

        SECTION("X^2 Check Interpolation"){
            value = cb10.integrate(x_square, -1.0, 1.0);
            printf("Integrating chebychev x^2 from -1 to 1 and the expected value is 0.392699081698 and found %f\n", value);
            REQUIRE_THAT(value, Catch::Matchers::WithinRel(0.392699081698, tol));
        }
    }
}
