#pragma once

#include <string>
#include <vector>
#include <iostream>

using namespace std;

// Shorthand type definition for an unsigned integer.
typedef unsigned int uint;

// Gets the user's input as a string after printing the prompt.
string get_input(string prompt);

// Prints the provided string to the terminal.
void print(string out);

// Gets a uint value from the user after displaying the prompt.
uint get_uint(string prompt);

// Gets a double value from the user after displaying the prompt.
double get_double(string prompt);