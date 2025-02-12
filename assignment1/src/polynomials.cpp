//
// Created by Fuad Hasan on 2/10/25.
//
#include "polynomials.h"
#include <math.h>
#include <stdexcept>

double Polynomial::operator()(double position) {
    double value = 0;
    for (int i = 0; i < coefficients_.size(); ++i) {
        value += coefficients_[i] * pow(position, i);
    }
    return value;
}

Polynomial::Polynomial(std::vector<double> coefficients) : coefficients_(coefficients){}

unsigned int Polynomial::getDegree() {
    return coefficients_.size() - 1;
}

double Polynomial::getCoefficient(unsigned int index) {
    // throw exception if index is out of range
    if (index >= coefficients_.size() || index < 0) {
        throw std::out_of_range("Index out of range\n");
    } else {
        return coefficients_[index];
    }
}