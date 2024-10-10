#include "DiffEq.h"

#include <sstream>
#include <fstream>

string DiffEq::build_general_equation(uint order)
{
    stringstream stream;

    for (uint i = order; i != -1; i--) {
        if (i != order) {
            stream << "a" << i << "*";
        }

        if (i != 0) {
            stream << "y^" << i << "(t) + ";
        }
        else {
            stream << "y(t)";
        }
    }

    stream << " = 0";

    return stream.str();
}

Matrix DiffEq::build_approximator(double resolution)
{
    return *this->_identity_matrix + (*this->_A_matrix * resolution);
}

DiffEq* DiffEq::from_input()
{
    const uint order = get_uint("Enter the order of your differential equation (>0): ");
    cout << "Equation structure: " << endl << build_general_equation(order) << endl;

    vector<double>* coefficients = new vector<double>;
    vector<double>* initial_conditions = new vector<double>;

    for (int i = 0; i < order; i++) {
        double coefficient = get_double("Enter value for coefficient a" + std::to_string(i) + ": ");
        double initial_condition;
        if (i == 0)
            initial_condition = get_double("Enter value for y(0): ");
        else
            initial_condition = get_double("Enter value for y^" + std::to_string(i) + "(t): ");

        coefficients->push_back(coefficient);
        initial_conditions->push_back(initial_condition);
    }

    return new DiffEq(order, coefficients, initial_conditions);
}

DiffEq::DiffEq(const uint order, const vector<double>* coefficients, const vector<double>* initial_conditions)
    : _order(order), _diff_coefficients(coefficients), _init_conditions(initial_conditions)
{
    this->_identity_matrix = Matrix::Identity(order);

    Matrix* aMatrix = new Matrix(order, order);
    // set ones
    for (uint row = 0, col = 1; row < order && col < order; row++, col++) {
        aMatrix->set_value(row, col, 1);
    }
    // set a values
    uint col = 0;
    for (double coefficient : *_diff_coefficients) {
        aMatrix->set_value(order - 1, col, -coefficient);
        col++;
    }

    this->_A_matrix = aMatrix;
}

DiffEq::~DiffEq()
{
    delete _diff_coefficients, _init_conditions, _A_matrix, _identity_matrix;
}

string DiffEq::to_string()
{
    stringstream stream;

    stream << "Differential equation structure: " << endl << build_general_equation(this->_order) << endl;

    stream << endl << "A Matrix: " << endl;
    stream << this->_A_matrix->to_string() << endl << "Initial condition: " << endl;
    
    for (uint i = 0; i < this->_order; i++) {
        if (i == 0)
            stream << "y(0) = ";
        else
            stream << "y^" << i << "(0) = ";

        stream << this->_init_conditions->at(i) << endl;
    }

    return stream.str();
}

Matrix* DiffEq::sample(double time, double resolution)
{
    if (time < 0)
        throw new invalid_argument("Cannot sample value t < 0 in this modal.");
    else if (resolution <= 0)
        throw new invalid_argument("Resolution must be greater than 0.");
    
    Matrix* y = new Matrix(this->_order, 1);
    for (uint row = 0; row < this->_order; row++) {
        y->set_value(row, 0, this->_init_conditions->at(row));
    }

    if (time == 0) {
        return y;
    }

    Matrix approximator = build_approximator(resolution);

    for (double t = 0; t <= time; t += resolution) {
        Matrix* temp = approximator * *y;
        delete y;  // delete the old y value from the heap since the * operator creates a new object

        y = temp;
    }

    return y;
}

bool DiffEq::export_range(double start, double end, double resolution, string filepath)
{
    if (start < 0 || end < 0)
        throw new invalid_argument("Cannot sample value t < 0 in this modal.");
    else if (end < start)
        throw new invalid_argument("End time must be greater than start time.");
    else if (resolution <= 0)
        throw new invalid_argument("Resolution must be greater than 0.");

    // Get value of y(start)
    Matrix* y = this->sample(start, resolution);
    Matrix approximator = build_approximator(resolution);

    ofstream file(filepath);

    for (double t = start; t <= end; t += resolution) {
        Matrix* temp = approximator * *y;
        delete y;  // delete the old y value from the heap since the * operator creates a new object

        y = temp;

        // Output value of t and y(t)
        file << t << " " << y->get_value(0, 0) << endl;
    }

    file.close();

    return true;
}
