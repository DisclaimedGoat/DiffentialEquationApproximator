#include "Global.h"

string get_input(string prompt)
{
    cout << prompt;
    string in;
    cin >> in;

    return in;
}

void print(string out)
{
    cout << out << endl;
}

uint get_uint(string prompt) {
    uint val = 0;

    do {
        val = stoi(get_input(prompt));
    } while (val <= 0);

    return val;
}

double get_double(string prompt) {
    string val = get_input(prompt);
    return stod(val);
}