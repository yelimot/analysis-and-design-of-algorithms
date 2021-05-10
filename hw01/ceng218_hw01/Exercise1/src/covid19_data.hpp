#ifndef POPULATION_DATA_HPP
#define POPULATION_DATA_HPP

#include <string>
#include <vector>

// Structure to store date, location, new cases, new deaths, total cases,
// and total deaths.
struct Covid19Data {
    std::string date;
    std::string location;
    int new_cases;
    int new_deaths;
    int total_cases;
    int total_deaths;
};

// A class to compare to Covid19Data object. The constructor takes parameters
// to customize sorting.
class Covid19DataCmp
{
public:
    Covid19DataCmp(bool by_new, bool by_case) {
        m_total = !by_new;
        m_death = !by_case;
    }

    bool operator()(const Covid19Data& cd0, const Covid19Data& cd1) const {
        if(m_total == false && m_death == false)
            return cd0.new_cases > cd1.new_cases;
        else if(m_total == true && m_death == false)
            return cd0.total_cases > cd1.total_cases;
        else if(m_total == false && m_death == true)
            return cd0.new_deaths > cd1.new_deaths;
        else
            return cd0.total_deaths > cd1.total_deaths;

    }
private:
    // private data fields are initialize during construction. They specify
    // how to compare to Covid19Data objects.
    bool m_total;
    bool m_death;
};

// Function to load Covid19Data from a CSV file.
void load_covid19_data(std::vector<Covid19Data> &covid19_Data,
                          const std::string &filename);

#endif