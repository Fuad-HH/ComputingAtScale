//
// Created by hasanm4 on 2/10/25.
//

#ifndef ASSIGNMENT1_POLYNOMIALS_H
#define ASSIGNMENT1_POLYNOMIALS_H
#include "scalar_function.h"
#include <vector>

class Polynomial : public ScalarFunction {
public:
    /**
     * Overridden operator() method to evaluate the polynomial at a given position
     * @param position: the position (-Inf, +Inf) at which the polynomial is to be evaluated
     * @return: the value of the polynomial at the given position
     */
    double operator()(double position) override;

    /**
     * Constructor for Polynomial class
     * @param coefficients: vector of coefficients of the polynomial (a0, a1, a2, ..., an)
     */
    Polynomial(std::vector<double> coefficients);

    /**
     * Method to get the degree of the polynomial
     * @return: the degree of the polynomial
     */
    unsigned int getDegree();

    /**
     * Get the coefficient of the polynomial at a given index
     */
    double getCoefficient(unsigned int index);

private:
    std::vector<double> coefficients_;
};

#endif //ASSIGNMENT1_POLYNOMIALS_H
