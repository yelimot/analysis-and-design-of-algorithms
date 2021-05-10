// Yasar Polatli 250201075

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>

#include "covid19_data.hpp"
#include "quicksort.hpp"

using namespace std;

void print_usage(const char *prog_name)
{
    cerr << "  --n <N>      : display top N items instead of 10" << endl;
    cerr << "Usage: " << prog_name << " <data-filename> [options]" << endl;
    cerr << "Options:" << endl;
    cerr << "  --by-total   : sort by totals instead of new" << endl;
    cerr << "  --by-deaths  : sort by deaths instead of cases" << endl;
}

// This program takes the CSV filename and options from the command line.
int main(int argc, char** argv)
{
    // We require at least a single command line argument, the filename of
    // the COVID-19 data
    if (argc < 2) {
        print_usage(argv[0]);
        return EXIT_FAILURE;
    }

    // By default sort in new cases. User can change the sort options.
    bool sort_new = true;
    bool sort_case = true;
    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "--by-total") == 0)
            sort_new = false;
        else if (strcmp(argv[i], "--by-deaths") == 0)
            sort_case = false;
    }

    // Load data from the CSV file.
    vector<Covid19Data> pop_data;
    load_covid19_data(pop_data, argv[1]);

    // By default, we sort by the topmost 10 data items. Parse command line
    // options to check if the user entered another option.
    int n=10;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(argv[i], "-n") == 0) {
            if (i == argc-1) {
                cerr << "Missing an integer after -n" << endl;
                print_usage(argv[0]);
                return EXIT_FAILURE;
            }

            i++;
            n = atoi(argv[i]);


            if (n < 1) {
                cerr << "You must enter an integer bigger or equal to one!" << endl;
                return EXIT_FAILURE;
            }
        }
    }

    // Sort the data using a Covid19DataCmp object for comparisons.
    quicksort_generic(pop_data, Covid19DataCmp(sort_new, sort_case));

    //Header
    string date = "Date|";
    cout << setw(5+(date.size()/2)) << "Date" << setw(4) <<"|"
         <<setw(10) << "New Cases" << "|"
         << setw(10) << "New Deaths" << "|"
         << setw(11) << "Total Cases" << "|"
         << setw(12) << "Total Deaths" << "|"
         << left << setw(12) << "Location"
         << endl;
    cout << "----------|----------|----------|-----------|------------|------------" << endl;

    // Output the population and city name in the sorted order.
    for (int i=0; i < pop_data.size() && i < n; i++) {
        cout << setw(10) << pop_data[i].date << "|"
             << right << setw(10) << pop_data[i].new_cases << "|"
             << right << setw(10) << pop_data[i].new_deaths << "|"
             << right << setw(11) << pop_data[i].total_cases << "|"
             << right << setw(12) << pop_data[i].total_deaths << "|"
             << left << setw(12) << pop_data[i].location
             << endl;
    }

    return EXIT_SUCCESS;
}