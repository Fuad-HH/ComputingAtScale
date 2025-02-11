//
// Created by hasanm4 on 2/10/25.
//

#ifndef ASSIGNMENT1_SCALAR_FUNCTION_H
#define ASSIGNMENT1_SCALAR_FUNCTION_H

class ScalarFunction {
public:
    /**
     * Evaluate the function at a given position
     * @param position The position to evaluate the function at
     * @return The value of the function at the given position
     * @note The child class constructors handle if the function is defined at the given position
     */
    virtual double operator()(double position) = 0;
};

#endif //ASSIGNMENT1_SCALAR_FUNCTION_H
