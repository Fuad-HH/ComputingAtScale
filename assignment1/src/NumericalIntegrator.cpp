//
// Created by hasanm4 on 2/10/25.
//

#include "NumericalIntegrator.h"
#include <cmath>
#include <stdexcept>

NumericalIntegrator::NumericalIntegrator(std::vector<double> points,
                                         std::vector<double> weights) :
                                         points_(points),
                                         weights_(weights) {}

std::vector<double>
NumericalIntegrator::normalizeInterval(std::vector<double> &points, double lower_bound, double upper_bound) {
    std::vector<double> normalized_points(points.size(), 0.0);

    for (int i = 0; i < points.size(); i++) {
        normalized_points[i] = ((upper_bound - lower_bound) / 2) * points[i] + (upper_bound + lower_bound) / 2;
    }

    return normalized_points;
}

double NumericalIntegrator::integrate(Polynomial &p, double lower_bound, double upper_bound) {
    if (std::abs(lower_bound - upper_bound) < 1e-10) {
        fprintf(stdout, "Warning: lower bound and upper bound are the same. Returning 0.\n");
        return 0.0;
    }
    auto normalized_points = normalizeInterval(points_, lower_bound, upper_bound);
    double range_normalization_factor = (upper_bound - lower_bound) / 2;
    return calculateIntegralInUnitRange(p, normalized_points, weights_) * range_normalization_factor;
}

double NumericalIntegrator::calculateIntegralInUnitRange(Polynomial &p, std::vector<double> &points,
                                                         std::vector<double> &weights) {
    double integral = 0;
    for (int i = 0; i < points.size(); i++) {
        integral += weights[i] * p(points[i]);
    }
    return integral;
}

GaussLegendre::GaussLegendre(int n) {
    switch (n) {
        case 1: {
            points_ = {0};
            weights_ = {2};
            break;
        }
        case 2: {
            points_ = {-1 / sqrt(3), 1 / sqrt(3)};
            weights_ = {1, 1};
            break;
        }
        case 3: {
            points_ = {-sqrt(3.0 / 5), 0, sqrt(3.0 / 5)};
            weights_ = {5.0 / 9, 8.0 / 9, 5.0 / 9};
            break;
        }
        case 4: {
            points_ = {-sqrt(3.0 / 7 + 2.0 / 7 * sqrt(6.0 / 5)),
                       -sqrt(3.0 / 7 - 2.0 / 7 * sqrt(6.0 / 5)),
                       sqrt(3.0 / 7 - 2.0 / 7 * sqrt(6.0 / 5)),
                       sqrt(3.0 / 7 + 2.0 / 7 * sqrt(6.0 / 5))};
            weights_ = {(18 - sqrt(30)) / 36,
                        (18 + sqrt(30)) / 36,
                        (18 + sqrt(30)) / 36,
                        (18 - sqrt(30)) / 36};
            break;
        }
        default: {
            throw std::runtime_error("Gauss-Legendre quadrature not implemented for n = " + std::to_string(n));
        }
    }
}

