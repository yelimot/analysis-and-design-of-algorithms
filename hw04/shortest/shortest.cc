/*
 * M. Yasar Polatli 250201075
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

// Adjacency matrix implementation of Dijkstra Algorithm
class ShortestPath {
public:

    ShortestPath() {
        cout << "Enter the adjacency list:" << endl;

        string line;
        getline(cin, line);
        m_V = stoi(line); // Size

        // Resize vectors and initialize
        graph.resize(m_V);
        shortest.resize(m_V);
        for (int i = 0; i < m_V; i++) {
            graph[i].resize(m_V);
            shortest[i] = inf;

            for (int j = 0; j < m_V; j++)
                graph[i][j] = -1;
        }

        vector<string> items;

        // Create weighted graph
        for (int i = 0; i < m_V; i++) {
            getline(cin, line);
            split_by_space(line, items);

            for (int j = 1; j < items.size(); j += 2) {
                graph[string_to_int(items[0])][string_to_int(items[j])] = stoi(items[j + 1]);
                graph[string_to_int(items[j])][string_to_int(items[0])] = stoi(items[j + 1]);
            }
        }

        find_shortest_path();
        print();
    }


private:
    vector<vector<int>> graph; // Weighted graph
    vector<double> shortest;
    int m_V;
    double inf = std::numeric_limits<double>::infinity(); // Infinity

    // Converts string to integer
    int string_to_int(string c) {
        return int(c.front()) - 97;
    }

    // Converts int to char
    char int_to_char(int i) {
        return char(i + 97);
    }

    void split_by_space(string &line, vector<string> &items) {
        items.clear();

        // while there are space in the line, split and push the first part
        // into items vector
        size_t space_pos = line.find(' ');
        while (space_pos != std::string::npos) {
            items.push_back(line.substr(0, space_pos));
            line = line.substr(space_pos + 1, line.size());
            space_pos = line.find(' ');
        }

        // push the remaining last item
        items.push_back(line);
    }

    void find_shortest_path() {
        // Start from a and for a we know that total weight is zero
        r_find_shortest_path(0, 0);
    }

    // Finds shortest parts using recursion
    void r_find_shortest_path(int current_item, int total_weight) {
        shortest[current_item] = total_weight;

        for (int i = 0; i < m_V; i++) {
            if (graph[current_item][i] != -1) {
                if (shortest[i] < total_weight + graph[current_item][i])
                    continue;
                r_find_shortest_path(i, (total_weight + graph[current_item][i]));
            }
        }
    }

    // Prints the result
    void print() {
        cout << endl;
        for (int i = 1; i < m_V; i++) {
            cout << int_to_char(i) << " " << shortest[i] << endl;
        }
    }
};


int main() {
    ShortestPath shortest = ShortestPath();
    return 0;
}
