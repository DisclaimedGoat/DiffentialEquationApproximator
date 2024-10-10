#pragma once

#include "Global.h"
#include "Matrix.h"

class DiffEq {
private:
    const uint _order;

    const vector<double> *_diff_coefficients;
    const vector<double>* _init_conditions;

    Matrix* _identity_matrix;
    Matrix* _A_matrix;

    static string build_general_equation(uint order);

    Matrix build_approximator(double resolution);

public:
    static DiffEq* from_input();

    DiffEq(const uint order, const vector<double>* coefficients, const vector<double>* initial_conditions);
    ~DiffEq();

    string to_string();

    // Estimates a value at t = time. Smaller resolution means higher accuracy but more time.
    Matrix* sample(double time, double resolution);

    bool export_range(double start, double end, double resolution, string filepath);
};