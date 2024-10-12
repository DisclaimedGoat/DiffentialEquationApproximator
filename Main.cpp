#include "Global.h"
#include "DiffEq.h"

int main()
{
    DiffEq* eq = DiffEq::from_input();
    cout << eq->to_string() << endl;

    string option = "";

    do {
        option = get_input("Sample (s), export (e), or quit (q): ");
        if (option == "s") {
            double t = get_double("Enter value to sample (>0): ");
            double resolution = get_double("Enter resolution for approximating y(t): ");

            cout << "y(" << t << ") = " << eq->sample(t, resolution)->to_string() << endl;
        }
        else if (option == "e") {
            double start = get_double("Enter start time to export: ");
            double end = get_double("Enter end time to export: ");
            double resolution = get_double("Enter resolution for approximating y(t): ");
            string filepath = get_input("Enter output path for export: ");

            cout << "Sampling values. Might take a few minutes..." << endl;

            eq->export_range(start, end, resolution, filepath);

            cout << "Export complete." << endl << endl;
        }
    } while (option != "q");

    cout << "Quitting." << endl;
}