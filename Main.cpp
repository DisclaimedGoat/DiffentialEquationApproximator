#include "Global.h"
#include "DiffEq.h"

int main()
{
    DiffEq* eq = DiffEq::from_input();
    cout << eq->to_string() << endl;

    double start = get_double("Enter start time to export: ");
    double end = get_double("Enter end time to export: ");
    double resolution = get_double("Enter resolution for approximating y(t): ");
    string filepath = get_input("Enter output path for export: ");

    cout << "Sampling values..." << endl;

    eq->export_range(start, end, resolution, filepath);

    cout << "Export complete." << endl << endl;

}
