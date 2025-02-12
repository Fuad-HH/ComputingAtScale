//
// Created by hasanm4 on 2/11/25.
//

#ifndef ASSIGNMENT1_READ_INTEGRATION_SETUP_H
#define ASSIGNMENT1_READ_INTEGRATION_SETUP_H

#include "NumericalIntegrator.h"
#include <string>
#include <memory>

struct PolynomialIntegrator {
    Polynomial polynomial;
    std::unique_ptr<NumericalIntegrator> integrator;
    double upperBound;
    double lowerBound;
};

// Helper functions to read data from file
PolynomialIntegrator readPolynomial(std::string filename);


#endif //ASSIGNMENT1_READ_INTEGRATION_SETUP_H
