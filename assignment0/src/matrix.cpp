//
// Created by hasanm4 on 1/16/25.
//

#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>

extern "C" {
#include "mmio.h"
}

//******************* Constructors *******************//
Matrix::Matrix(int rows, int cols): rows_(rows), cols_(cols) {
    data_.resize(rows_*cols_);
    // initialize data to 0
    for (int i = 0; i < data_.size(); i++) {
        data_[i] = 0.0;
    }
}

Matrix::Matrix(const std::vector<double> &data_in, int rows, int cols) : rows_(rows), cols_(cols), data_(data_in) {
    // validate data_in size
    if (data_in.size() != rows*cols || rows < 0 || cols < 0) {
        throw std::invalid_argument("[ERROR] Matrix data size does not match the matrix size\n");
    }
}

Matrix::Matrix(const Matrix &m) {
    rows_ = m.rows_;
    cols_ = m.cols_;
    data_ = m.data_;
}

Matrix::Matrix(const char *mfilename) {
    MM_typecode matcode;

    auto *file_to_read = fopen(mfilename, "r");
    if (file_to_read == NULL)
    {
        printf("File not found\n");
        exit(1);
    }

    if (mm_read_banner(file_to_read, &matcode) != 0) {
        printf("Could not process Matrix Market banner for file 1.\n");
        exit(1);
    }

    if (!mm_is_real(matcode)){
        printf("Works only for real valued matrices\n");
        exit(1);
    }

    if (!mm_is_array(matcode)){
        printf("Works only for array matrices since we are only working for dense matrices\n");
        exit(1);
    }

    if (mm_read_mtx_array_size(file_to_read, &rows_, &cols_) != 0) {
        printf("Could not read matrix size for file.\n");
        exit(1);
    }

    data_.resize(rows_*cols_);

    // TODO: how to check if it contains the right number of elements
    for (int i = 0; i < rows_*cols_; i++) {
        fscanf(file_to_read, "%lf\n", &data_[i]);
    }

    if (file_to_read != stdin) {fclose(file_to_read);}
}

//******************* Destructor *******************//

Matrix::~Matrix() {}

//******************* Public Methods *******************//
void Matrix::operator*(const double scalar) {
    for (int i = 0; i < data_.size(); i++) {
        data_[i] *= scalar;
    }
}

void Matrix::operator/(const double scalar) {
    for (int i = 0; i < data_.size(); i++) {
        data_[i] /= scalar;
    }
}

bool Matrix::operator==(Matrix &matrix) {
    if (rows_ != matrix.getRows() || cols_ != matrix.getCols()) {
        return false;
    }

    auto mat_data = matrix.getData();
    for (int i = 0; i < data_.size(); i++) {
        // relative error: <= 1e-6
        if (std::abs(mat_data[i] - data_[i])/data_[i] > 1e-6) {
            return false;
        }
    }
    return true;
}

int Matrix::getCols() const {
    return cols_;
}

int Matrix::getRows() const {
    return rows_;
}

std::vector<double> Matrix::getData() const {
    return data_;
}

std::vector<double> Matrix::operator*(const std::vector<double> &vector) const{
    if (vector.size() != cols_) {
        return std::vector<double>();
    } else {
        std::vector<double> result(rows_, 0.0);

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < cols_; j++) {
                result[i] += data_[i*cols_ + j] * vector[j]; // ? is there any advantage of using operator()
            }
        }
        return result;
    }
}

double& Matrix::operator()(int row, int col){
    return data_[row*cols_ + col];
}

std::vector<double> vectorMatrixMult(const std::vector<double> &vector, Matrix &matrix) {
    // validate vector size
    if (vector.size() != matrix.getRows()) {
        return std::vector<double>();
    } else {
        std::vector<double> result(matrix.getCols(), 0.0);

        for (int i = 0; i < matrix.getCols(); i++) {
            for (int j = 0; j < matrix.getRows(); j++) {
                result[i] += vector[j] * matrix(j,i);
            }
        }
        return result;
    }
}

void Matrix::writeMatrixMarket(const char *mfilename) const {
    MM_typecode matcode;

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_array(&matcode);
    mm_set_real(&matcode);

    auto *file_to_write = fopen(mfilename, "w");
    if (file_to_write == NULL)
    {
        printf("Cannot create file\n");
        exit(1);
    }

    mm_write_banner(file_to_write, matcode);
    mm_write_mtx_array_size(file_to_write, rows_, cols_);

    // row major matrix
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fprintf(file_to_write, "%lf\n", data_[i*cols_ + j]);
        }
    }
    fclose(file_to_write);
    printf("INFO: Matrix written to file: %s\n", mfilename);
}

Matrix Matrix::operator*(Matrix &matrix) {
    // validate matrix size
    if (cols_ != matrix.getRows()) {
        return Matrix(0,0);
    } else {
        Matrix result(rows_, matrix.getCols());

        for (int i = 0; i < rows_; i++) {
            for (int j = 0; j < matrix.getCols(); j++) {
                for (int k = 0; k < cols_; k++) {
                    result(i,j) += data_[i*cols_ + k] * matrix(k,j);
                }
            }
        }
        return result;
    }
}

void Matrix::print() const {
    printf("\nRows: %d, Cols: %d\n", rows_, cols_);
    printf("Data:\n");
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            printf("%10.3g ", data_[i*cols_ + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void Matrix::printMatrixMarket() const {
    MM_typecode matcode;

    mm_initialize_typecode(&matcode);
    mm_set_matrix(&matcode);
    mm_set_array(&matcode);
    mm_set_real(&matcode);

    mm_write_banner(stdout, matcode);
    mm_write_mtx_array_size(stdout, rows_, cols_);

    // row major matrix
    for (int i = 0; i < rows_; i++) {
        for (int j = 0; j < cols_; j++) {
            fprintf(stdout, "%lf\n", data_[i*cols_ + j]);
        }
    }
}
