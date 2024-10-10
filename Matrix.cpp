#include "Matrix.h"

#include <sstream>

Matrix* Matrix::Identity(uint size)
{
    // Ensure size is at least 1.
    if (size < 1) {
        throw new invalid_argument("Size parameter for identity matrix must be greater than zero.");
    }

    Matrix* matrix = new Matrix(size, size);

    // fill with identity matrix pattern
    for (uint row = 0, col = 0; row < size && col < size; row++, col++) {
        // Fill in ones in the diagonal.
        matrix->set_value(row, col, 1);
    }

    return matrix;
}

Matrix::Matrix(uint sizeM, uint sizeN) : _sizeM(sizeM), _sizeN(sizeN)
{
    // Create the 2D vector on the heap.
    _matrix = new vector<vector<double>>;
    
    // create vectors for each row
    for (uint i = 0; i < sizeM; i++) {

        // create the new row
        vector<double> row;
        for (uint j = 0; j < sizeN; j++) {
            // fill zeros for each element in the row
            row.push_back(0);
        }

        _matrix->push_back(row);
    }
}

Matrix::~Matrix() {
    delete _matrix;
}

double Matrix::get_value(uint row, uint col)
{
    return _matrix->at(row)[col];
}

void Matrix::set_value(uint row, uint col, double value)
{
    _matrix->at(row).at(col) = value;
}

uint Matrix::get_sizem()
{
    return _sizeM;
}

uint Matrix::get_sizen()
{
    return _sizeN;
}

Matrix& Matrix::operator+(Matrix &b)
{
    if (_sizeM != b._sizeM || _sizeN != b._sizeN)
        throw new invalid_argument("Matrix b must be exactly the same size to add.");

    // Create a new matrix object.
    Matrix* newMatrix = new Matrix(_sizeM, _sizeN);

    for (uint row = 0; row < _sizeM; row++) {
        for (uint col = 0; col < _sizeN; col++) {
            double sum = get_value(row, col) + b.get_value(row, col);
            newMatrix->set_value(row, col, sum);
        }
    }

    return *newMatrix;
}

Matrix& Matrix::operator-(Matrix& b)
{
    if (_sizeM != b._sizeM || _sizeN != b._sizeN)
        throw new invalid_argument("Matrix b must be exactly the same size to subtract.");

    // Create a new matrix object.
    Matrix* newMatrix = new Matrix(_sizeM, _sizeN);

    for (uint row = 0; row < _sizeM; row++) {
        for (uint col = 0; col < _sizeN; col++) {
            double difference = get_value(row, col) - b.get_value(row, col);
            newMatrix->set_value(row, col, difference);
        }
    }

    return *newMatrix;
}

Matrix* Matrix::operator*(Matrix& b)
{
    // m*n X n*p = m*p
    if (_sizeN != b._sizeM)
        throw new invalid_argument("Matrix b is not compatible to multiply");

    Matrix* newMatrix = new Matrix(_sizeM, b._sizeN);

    for (uint row = 0; row < _sizeM; row++) {
        for (uint col = 0; col < b._sizeN; col++) {
            double sum = 0;

            for (uint colA = 0, rowB = 0; colA < _sizeN && rowB < b._sizeM; colA++, rowB++) {
                sum += get_value(row, colA) * b.get_value(rowB, col);
            }

            newMatrix->set_value(row, col, sum);
        }
    }

    return newMatrix;
}

Matrix& Matrix::operator*(double scale)
{
    // Create a new matrix object.
    Matrix* newMatrix = new Matrix(_sizeM, _sizeN);

    // For each element, multiply by scale
    for (uint row = 0; row < _sizeM; row++) {
        for (uint col = 0; col < _sizeN; col++) {
            double scaled = get_value(row, col) * scale;
            newMatrix->set_value(row, col, scaled);
        }
    }

    return *newMatrix;
}

string Matrix::to_string()
{
    stringstream stream;

    for (uint row = 0; row < this->_sizeM; row++) {
        stream << "[ ";
        for (uint col = 0; col < this->_sizeN; col++) {
            stream << get_value(row, col) << " ";
        }

        stream << "]";
        if (row + 1 != _sizeM) {
            stream << endl;
        }
    }

    return stream.str();
}
