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

enum class ChebyshevType {
    FIRST_KIND,
    SECOND_KIND
};

class Chebychev : public NumericalIntegrator {
public:

    /**
     * Constructor for Chebyshev–Gauss quadrature
     * @param n the number of points to use
     * @param type the type of Chebychev to use: available options are ChebyshevType::FIRST_KIND and ChebyshevType::SECOND_KIND
     */
    Chebychev(int n, ChebyshevType type);

    /**
     * * Integrates the Chebyshev for p over the interval -1 to 1
     * @param p
     * @param lower_bound must be -1
     * @param upper_bound must be 1
     * @return the integral of the polynomial over the interval -1 to 1
     */
    double integrate(Polynomial &p, double lower_bound=-1.0, double upper_bound=1.0) override;

    std::vector<double> getChebychevPoints();
    std::vector<double> getChebychevWeights();

private:
    ChebyshevType type_;
};

#endif //ASSIGNMENT1_NUMERICALINTEGRATOR_H
