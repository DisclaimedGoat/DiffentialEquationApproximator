#pragma once

#include "Global.h"

// Represents a matrix object with size m*n.
struct Matrix {
private:
    // The size of the matrix. Unchanging
    const uint _sizeM, _sizeN;

    // 2D vector pointer that stores the contents of the matrix.
    vector<vector<double>> *_matrix;

public:
    // Create a standard identity matrix of size n*n
    static Matrix* Identity(uint n);

    // Create a new matrix with sizeM*sizeN;
    Matrix(uint sizeM, uint sizeN);

    template <uint sizeM, uint sizeN>
    // Creates a matrix from a reference to a 2D array.
    Matrix(double(&arr)[sizeM][sizeN]) : _sizeM(sizeM), _sizeN(sizeN)
    {
        _matrix = new vector<vector<double>>;

        for (uint i = 0; i < sizeM; i++) {

            vector<double> row;
            for (uint j = 0; j < sizeN; j++) {
                row.push_back(arr[i][j]);
            }

            _matrix->push_back(row);
        }
    }

    ~Matrix();

    // Gets the value of the matrix at a particular row/column pair.
    double get_value(uint row, uint col);

    // Sets the value of the matrix at a particular row/column pair.
    void set_value(uint row, uint col, double value);

    // Returns the number of rows (m) in this matrix.
    uint get_sizem();

    // Returns the number of columns (n) in this matrix.
    uint get_sizen();

    // Creates a matrix from the sum of two matrices.
    // The matrices but be equal in dimension.
    Matrix* operator+(Matrix &b);
    
    // Creates a matrix from the difference of two matrices.
    // The matrices but be equal in dimension.
    Matrix* operator-(Matrix &b);

    // Creates a matrix from the product of two matrices.
    // The matrices must match the following pattern: m*n X n*p = m*p
    Matrix* operator*(Matrix &b);

    // Scales each value in the matrix by the given value.
    Matrix* operator*(double scale);

    // Converts this matrix object into a formatted string.
    string to_string();
};