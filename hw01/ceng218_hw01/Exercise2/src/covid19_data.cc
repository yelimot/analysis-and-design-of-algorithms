#include "covid19_data.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>

using namespace std;

// Given a single line of text, it splits the line by commas and fills the items
// vector with each one. Destroys the contents of the line during the process.
void split_by_commas(string &line, vector<string> &items)
{
    items.clear();

    // while there are commas in the line, split and push the first part
    // into items vector
    size_t comma_pos = line.find(',');
    while (comma_pos != std::string::npos) {
        items.push_back(line.substr(0, comma_pos));
        line = line.substr(comma_pos+1, line.size());
        comma_pos = line.find(',');
    }

    // push the remaining last item
    items.push_back(line);
}


void load_covid19_data(std::vector<Covid19Data> &covid19_data,
                          const std::string &filename)
{
    covid19_data.clear();

    ifstream fin(filename);
    if (!fin.good()) {
        cerr << "Error opening city data file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    // read header
    string line;
    getline(fin, line);

    vector<string> items;

    // for each remaining line, read the date, location, new cases, new deaths,
    // total cases, total deaths.
    while (getline(fin, line)) {
        split_by_commas(line, items);
        Covid19Data cd;

        cd.date = items[0];
        cd.location = items[1];
        cd.new_cases = stoi(items[2]);
        cd.new_deaths = stoi(items[3]);
        cd.total_cases = stoi(items[4]);
        cd.total_deaths = stoi(items[5]);

        covid19_data.push_back(cd);
    }

    fin.close();
}