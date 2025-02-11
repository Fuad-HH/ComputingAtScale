//
// Created by hasanm4 on 2/10/25.
//

#ifndef ASSIGNMENT1_NUMERICALINTEGRATOR_H
#define ASSIGNMENT1_NUMERICALINTEGRATOR_H

#include "polynomials.h"
#include <vector>


class NumericalIntegrator {
public:
    virtual double integrate(Polynomial &p, double lower_bound, double upper_bound);

    virtual std::vector<double> normalizeInterval(std::vector<double>& points, double lower_bound, double upper_bound);

    NumericalIntegrator(std::vector<double> points, std::vector<double> weights);
    NumericalIntegrator() : points_(), weights_() {}

protected:
    double calculateIntegralInUnitRange(Polynomial &p, std::vector<double>& points, std::vector<double>& weights);

    std::vector<double> points_;
    std::vector<double> weights_;
};


class GaussLegendre : public NumericalIntegrator {
public:
    GaussLegendre(int n);
};

#endif //ASSIGNMENT1_NUMERICALINTEGRATOR_H
