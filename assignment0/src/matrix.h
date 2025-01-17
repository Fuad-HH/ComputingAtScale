//
// Created by hasanm4 on 1/16/25.
//

#ifndef ASSIGNMENT0_MATRIX_H
#define ASSIGNMENT0_MATRIX_H

#include <vector>

/**
 * Matrix
 * A simple matrix class to hold 2D matrices based on std::vector
 *
 * Row major order is used
 */
class Matrix {
private:
    int rows_;
    int cols_;
    // linear data
    std::vector<double> data_;

public:
    Matrix() {rows_=0; cols_=0;}
    // Initialize matrix with zeros
    Matrix(int rows, int cols);

    // Initialize matrix with data
    Matrix(const std::vector<double> &data_in, int rows, int cols);

    // Copy constructor
    Matrix(const Matrix &matrix);

    // read matrix market file
    Matrix(const char *mfilename);

    // Destructor
    ~Matrix();

    // Getters
    int getRows() const;
    int getCols() const;
    std::vector<double> getData() const;

    // operator overloading (inplace)
    void operator*(const double scalar);
    void operator/(const double scalar);
    bool operator==(Matrix &matrix);

    // index operator
    double& operator()(int row, int col);

    Matrix operator*(Matrix &matrix);

    void print() const;
    void printMatrixMarket() const;

    // matrix * vector
    std::vector<double> operator*(const std::vector<double> &vector) const;

    // vector * matrix friend function
    friend std::vector<double> vectorMatrixMult(const std::vector<double> &vector, Matrix &matrix);

    // write matrix to file in Matrix Market format
    void writeMatrixMarket(const char *mfilename) const;
};


#endif //ASSIGNMENT0_MATRIX_H
