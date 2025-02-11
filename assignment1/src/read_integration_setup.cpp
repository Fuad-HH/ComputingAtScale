//
// Created by hasanm4 on 2/11/25.
//

#include "read_integration_setup.h"
#include <vector>
#include <fstream>
#include <stdexcept>
#include <cassert>

PolynomialIntegrator readPolynomial(std::string filename) {
    // try to open the file
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file " + filename);
    }

    // read the degree of the polynomial: first line of the file
    int degree;
    file >> degree;
    if (degree <= 0) {
        throw std::runtime_error("Invalid degree " + std::to_string(degree));
    } else {
        printf("Degree: %d\n", degree);
    }

    int type;
    file >> type; // 0 for Gauss-Legendre, 1 for Chebyshev kind 1, 2 for Chebyshev kind 2
    if (type < 0 || type > 2) {
        throw std::runtime_error("Invalid Integration type " + std::to_string(type) +
                                 "\n 0 for Gauss-Legendre, 1 for Chebyshev kind 1, 2 for Chebyshev kind 2");
    } else {
        printf("Integration Type: [%d] ", type);
        if (type == 0) {
            printf("Gauss-Legendre\n");
        } else if (type == 1) {
            printf("Chebyshev kind 1\n");
        } else if (type == 2) {
            printf("Chebyshev kind 2\n");
        }
    }

    // read the upper and lower bounds of the integral: second line of the file
    double lowerBound, upperBound;
    file >> lowerBound >> upperBound; // not used when chebyshev
    if (lowerBound >= upperBound) {
        std::string message = "Invalid bounds: " + std::to_string(lowerBound) + " " + std::to_string(upperBound);
        message += "\nLower bound must be less than upper bound";
        throw std::runtime_error(message);
    }
    if ((type != 0) && (std::abs(upperBound - 1.0) > 1e-10 || std::abs(lowerBound + 1.0) > 1e-10)) {
        std::string message = "Invalid bounds: " + std::to_string(lowerBound) + " " + std::to_string(upperBound);
        message += "\nBounds must be -1.0 and 1.0 for Chebyshev polynomials";
        throw std::runtime_error(message);
    }
    printf("Bounds: %f %f\n", lowerBound, upperBound);

    // read number of points for Gauss-Legendre
    int numPoints;
    file >> numPoints;
    if (numPoints < 1) {
        throw std::runtime_error("Invalid number of points " + std::to_string(numPoints));
    } else {
        printf("Number of integration points: %d\n", numPoints);
    }

    // read the coefficients of the polynomial: third line of the file
    std::vector<double> coefficients(degree + 1);
    try {
        for (int i = 0; i <= degree; i++) {
            if (!(file >> coefficients[i])) {
                throw std::runtime_error("File ended before reading all coefficients");
            }
        }
    } catch (const std::exception &e) {
        file.close();
        throw;
    }
    printf("Given coefficients: ");
    for (int i = 0; i <= degree; i++) {
        printf("%f ", coefficients[i]);
    }
    printf("\n");

    // close the file
    file.close();

    // create the polynomial
    assert(coefficients.size() == degree + 1);
    Polynomial polynomial(coefficients);

    // create the integrator
    if (type == 0) {
        return {polynomial, std::make_unique<GaussLegendre>(numPoints), upperBound, lowerBound};
    } else if (type == 1) {
        return {polynomial, std::make_unique<Chebychev>(numPoints, ChebyshevType::FIRST_KIND), upperBound, lowerBound};
    } else if (type == 2) {
        return {polynomial, std::make_unique<Chebychev>(numPoints, ChebyshevType::SECOND_KIND), upperBound, lowerBound};
    } else {
        throw std::runtime_error("Invalid type " + std::to_string(type));
    }
}