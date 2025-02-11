//
// Created by Fuad Hasan on 2/10/25.
//

#include "polynomials.h"
#include <iostream>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("Test Polynomial Class") {
    double tol = 1e-10;

    SECTION("polynomial x^2") {
        std::vector<double> coeffs{0, 0, 1}; // x^2
        Polynomial x_squared(coeffs);

        REQUIRE_THAT(x_squared(1.0), Catch::Matchers::WithinAbs(1.0, tol));
        REQUIRE_THAT(x_squared(2.0), Catch::Matchers::WithinAbs(4.0, tol));
        REQUIRE_THAT(x_squared(-2.0), Catch::Matchers::WithinAbs(4.0, tol));
        REQUIRE_THAT(x_squared(0), Catch::Matchers::WithinAbs(0.0, tol));

        REQUIRE(x_squared.getDegree() == 2);
        REQUIRE_THAT(x_squared.getCoefficient(0), Catch::Matchers::WithinAbs(0.0, tol));
        REQUIRE_THAT(x_squared.getCoefficient(1), Catch::Matchers::WithinAbs(0.0, tol));
        REQUIRE_THAT(x_squared.getCoefficient(2), Catch::Matchers::WithinAbs(1.0, tol));

        REQUIRE_THROWS_AS(x_squared.getCoefficient(3), std::out_of_range);
        REQUIRE_THROWS_AS(x_squared.getCoefficient(-1), std::out_of_range);
        REQUIRE_THROWS_AS(x_squared.getCoefficient(10), std::out_of_range);
    }

    SECTION("polynomial 2x^2 + 3x + 4") {
        std::vector<double> coeffs{4, 3, 2}; // 2x^2 + 3x + 4
        Polynomial poly(coeffs);

        REQUIRE_THAT(poly(1.0), Catch::Matchers::WithinAbs(9.0, tol));
        REQUIRE_THAT(poly(2.0), Catch::Matchers::WithinAbs(18.0, tol));
        REQUIRE_THAT(poly(-2.0), Catch::Matchers::WithinAbs(6.0, tol));
        REQUIRE_THAT(poly(0), Catch::Matchers::WithinAbs(4.0, tol));

        REQUIRE(poly.getDegree() == 2);
        REQUIRE_THAT(poly.getCoefficient(0), Catch::Matchers::WithinAbs(4.0, tol));
        REQUIRE_THAT(poly.getCoefficient(1), Catch::Matchers::WithinAbs(3.0, tol));
        REQUIRE_THAT(poly.getCoefficient(2), Catch::Matchers::WithinAbs(2.0, tol));

        REQUIRE_THROWS_AS(poly.getCoefficient(3), std::out_of_range);
        REQUIRE_THROWS_AS(poly.getCoefficient(-1), std::out_of_range);
        REQUIRE_THROWS_AS(poly.getCoefficient(10), std::out_of_range);
    }
}
