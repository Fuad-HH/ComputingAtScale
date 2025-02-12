//
// Created by hasanm4 on 1/16/25.
//

#include <iostream>
#include <vector>
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "matrix.h"

TEST_CASE("Matrix Read: 2x2 Matrix"){
    Matrix matrix2x2("matrix2x2.txt");
    matrix2x2.print();

    REQUIRE(matrix2x2.getRows() == 2);
    REQUIRE(matrix2x2.getCols() == 2);
    REQUIRE_THAT(matrix2x2(0, 0), Catch::Matchers::WithinRel(1.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(0, 1), Catch::Matchers::WithinRel(2.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(1, 0), Catch::Matchers::WithinRel(3.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(1, 1), Catch::Matchers::WithinRel(4.0, 0.0000001));
}

TEST_CASE("Matrix Read: 2x2 Matrix with Comment") {
    Matrix matrix2x2("matrix2x2-with-comment.txt");
    matrix2x2.print();

    REQUIRE(matrix2x2.getRows() == 2);
    REQUIRE(matrix2x2.getCols() == 2);

    REQUIRE_THAT(matrix2x2(0, 0), Catch::Matchers::WithinRel(1.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(0, 1), Catch::Matchers::WithinRel(2.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(1, 0), Catch::Matchers::WithinRel(3.0, 0.0000001));
    REQUIRE_THAT(matrix2x2(1, 1), Catch::Matchers::WithinRel(4.0, 0.0000001));
}

TEST_CASE("Matrix Write: 2x2 Matrix"){
    std::vector<double> data = {2.0,3.0, 4.5, 5.5};
    Matrix matrix2x2(data, 2, 2);
    matrix2x2.writeMatrixMarket("matrixmarket2x2.log");

    Matrix read_matrix2x2("matrixmarket2x2.log");
    REQUIRE_THAT(read_matrix2x2(0,0), Catch::Matchers::WithinRel(matrix2x2(0,0), 0.0000001));
    REQUIRE_THAT(read_matrix2x2(0,1), Catch::Matchers::WithinRel(matrix2x2(0,1), 0.0000001));
    REQUIRE_THAT(read_matrix2x2(1,0), Catch::Matchers::WithinRel(matrix2x2(1,0), 0.0000001));
    REQUIRE_THAT(read_matrix2x2(1,1), Catch::Matchers::WithinRel(matrix2x2(1,1), 0.0000001));
}