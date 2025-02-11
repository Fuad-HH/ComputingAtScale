//
// Created by Fuad Hasan on 2/10/25.
//

#include <iostream>
#include "NumericalIntegrator.h"
#include "read_integration_setup.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    try {
        PolynomialIntegrator polyInt = readPolynomial(argv[1]);
        double integral = polyInt.integrator->integrate(polyInt.polynomial, polyInt.lowerBound, polyInt.upperBound);

        printf("\n=========> Integrating <=========\n");
        printf("Integral: %f\n", integral);
        printf("=================================\n");

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}