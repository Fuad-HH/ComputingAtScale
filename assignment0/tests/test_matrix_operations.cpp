//
// Created by hasanm4 on 1/16/25.
//

#include <iostream>
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "matrix.h"

TEST_CASE("Test Matrix Constructors") {
    REQUIRE_THROWS_AS(Matrix({1,2,3}, 2, 1), std::invalid_argument);
    REQUIRE_NOTHROW(Matrix({}, 0, 0));
}

TEST_CASE("Matrix-Vector and Vector-Matrix Multiplication: Passing"){
    Matrix A({1, 2, 3, 4}, 2, 2);
    std::vector<double> x = {1, 2};

    std::vector<double> y = A * x;
    std::vector<double> z = vectorMatrixMult(x, A);

    printf("y = [%f, %f]\n", y[0], y[1]);
    printf("z = [%f, %f]\n", z[0], z[1]);

    REQUIRE_THAT(y[0], Catch::Matchers::WithinAbs(5, 1e-6));
    REQUIRE_THAT(y[1], Catch::Matchers::WithinAbs(11, 1e-6));

    REQUIRE_THAT(z[0], Catch::Matchers::WithinAbs(7, 1e-6));
    REQUIRE_THAT(z[1], Catch::Matchers::WithinAbs(10, 1e-6));
}

TEST_CASE("Matrix-Vector and Vector-Matrix Multiplication: Failing [Dimension Mismatch]"){
    Matrix A({1, 2, 3, 4}, 2, 2);
    std::vector<double> x = {1, 2, 3};
    std::vector<double> y = A * x;
    std::vector<double> z = vectorMatrixMult(x, A);

    REQUIRE(y.size() == 0);
    REQUIRE(z.size() == 0);
}

TEST_CASE("Matrix-Matrix Multiplication: Passing") {
    // A =
    //    | 1 2 3 |
    //    | 4 5 6 |
    Matrix A({1, 2, 3, 4, 5, 6}, 2, 3);

    // B =
    //    | 7 8 13 |
    //    | 9 10 14 |
    //    | 11 12 15 |
    Matrix B({7, 8, 13, 9, 10, 14, 11, 12, 15}, 3, 3);

    Matrix C = A * B;

    // C = A * B =
    //    | 58  64  86 |
    //    | 139 154 212|
    Matrix C_expected({58, 64, 86, 139, 154, 212}, 2, 3);

    REQUIRE(C_expected == C);
}

TEST_CASE("Matrix-Matrix Multiplication: Failing [Dimension Mismatch]") {
    // A =
    //    | 1 2 3 |
    //    | 4 5 6 |
    Matrix A({1, 2, 3, 4, 5, 6}, 2, 3);

    // B =
    //    | 7  8|
    //    | 13 9|
    Matrix B({7, 8, 13, 9}, 2, 2);

    Matrix C = A * B;

    REQUIRE(C.getRows() == 0);
    REQUIRE(C.getCols() == 0);
}