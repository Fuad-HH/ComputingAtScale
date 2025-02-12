//
// Created by hasanm4 on 2/10/25.
//

#include "NumericalIntegrator.h"
#include <cmath>
#include <stdexcept>
#include <cassert>

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
    assert(points.size() == weights.size());
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

Chebychev::Chebychev(int n, ChebyshevType type) {
    if (n < 1) {
        throw std::runtime_error("Chebyshev polynomial order must be at least 1.");
    }
    points_ = std::vector<double>(n, 0.0);
    weights_ = std::vector<double>(n, 0.0);
    switch (type) {
        case ChebyshevType::FIRST_KIND: {
            for (int i = 0; i < n; i++) {
                points_[i] = cos((2*(i+1) -1)/(2.0*n) * M_PI);
                weights_[i] = M_PI / double(n);
            }
            break;
        }
        case ChebyshevType::SECOND_KIND: {
            for (int i = 0; i < n; i++) {
                points_[i] = cos((i+1) * M_PI / (n + 1));
                weights_[i] = M_PI / double(n+1) * std::pow(sin((i+1)*M_PI/(n+1)), 2);
            }
            break;
        }
        default: {
            throw std::runtime_error("Chebyshev type not implemented.");
        }
    }
}

double Chebychev::integrate(Polynomial &p, double lower_bound, double upper_bound) {
    if (std::abs(lower_bound + 1.0) > 1e-10 || std::abs(upper_bound - 1.0) > 1e-10) {
        throw std::runtime_error("Chebyshev polynomials are defined on the interval [-1, 1]. and only support this interval.");
    }
    return calculateIntegralInUnitRange(p, points_, weights_);
}

std::vector<double> Chebychev::getChebychevPoints() {
    return points_;
}

std::vector<double> Chebychev::getChebychevWeights() {
    return weights_;
}

