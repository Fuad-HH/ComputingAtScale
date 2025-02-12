//
// Created by Fuad Hasan on 1/16/25.
//
#include <string>
#include "matrix.h"

int main(int argc, char* argv[])
{
    // read the matrix from the files
    if (argc != 4){
        std::printf("Usage: %s <mat file 1> <mat file 2> <format(0: mat*vec 1:mat-mat)>\n", argv[0]);
        return 1;
    }
    std::string input_file1  = argv[1];
    std::string input_file2 = argv[2];
    int format = std::stoi(argv[3]);
    if (format != 0 && format != 1) {
        std::printf("Invalid format. Please enter 0 or 1\n");
        return 1;
    }

    Matrix mat1 = Matrix(input_file1.c_str());
    printf("The first matrix (%s): \n", input_file1.c_str());
    mat1.print();

    Matrix mult_mat;

    if (format == 1) {
        Matrix mat2 = Matrix(input_file2.c_str());
        printf("The second matrix (%s): \n", input_file2.c_str());
        mat2.print();

        mult_mat = mat1 * mat2;
    }

    if (format == 0) {
        Matrix vec = Matrix(input_file2.c_str());
        printf("The vector (%s): \n", input_file2.c_str());
        vec.print();

        // one of the dimensions of the matrix should be 1 to be a vector
        if (vec.getCols() != 1 && vec.getRows() != 1) {
            std::printf("ERROR: This should be a vector to multiply with another vector.\n");
            return 1;
        }

        std::vector<double> mult_vec = mat1 * vec.getData();

        mult_mat = Matrix(mult_vec, mat1.getRows(), 1);
    }

    printf("Product: \n");
    mult_mat.print();

    printf("\nResult Matrix in Matrix Market format: \n--------------------------------------------\n");
    mult_mat.printMatrixMarket();
    printf("\n--------------------------------------------\n");

    return 0;
}
