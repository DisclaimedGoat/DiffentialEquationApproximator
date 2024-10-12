#pragma once

#include "Global.h"
#include "Matrix.h"

// Class that contains information for a differential equation to approximate.
class DiffEq {
private:
    // The order of the diff. eq.
    const uint _order;

    // The coefficients of each diff. term (excluding the highest order diff.)
    const vector<double> *_diff_coefficients;

    // The initial conditions for each diff. term (exluding the highest order diff.)
    const vector<double>* _init_conditions;

    // Pointer storing the properly sized identity matrix
    Matrix* _identity_matrix;

    // Pointer storing the formatted A matrix
    Matrix* _A_matrix;

    // Builds the general form of the diff. eq. for a given order as a string.
    static string build_general_equation(uint order);

    // Builds the approximator matrix to multiply for sampling.
    Matrix build_approximator(double resolution);

public:
    // Builds a proper diff. eq. from getting input from the user.
    static DiffEq* from_input();

    // Constructs a DiffEq object.
    DiffEq(const uint order, const vector<double>* coefficients, const vector<double>* initial_conditions);

    // Deconstructor to delete items from the heap properly.
    ~DiffEq();

    // Creates a neat string that holds all data relating to this diff. eq.
    string to_string();

    // Estimates a value at t = time. Smaller resolution means higher accuracy but more time.
    Matrix* sample(double time, double resolution);

    // Export a range of values between a start and end time to a given file.
    bool export_range(double start, double end, double resolution, string filepath);
};