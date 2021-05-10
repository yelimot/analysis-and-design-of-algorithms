/*
 * M. Yasar Polatli 250201075
 */

#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

// Adjacency matrix implementation of Prim's Algorithm
class MST {
public:

    MST() {
        cout << "Enter the adjacency list:" << endl;

        total_weight = 0;

        string line;
        getline(cin, line);
        m_V = stoi(line); // Size

        // Resize vectors and initialize
        graph.resize(m_V);
        minimum_spanning_tree.resize(m_V);
        marked.resize(m_V);
        for (int i = 0; i < m_V; i++) {
            graph[i].resize(m_V);
            minimum_spanning_tree[i].resize(m_V);
            marked[i] = false;

            for (int j = 0; j < m_V; j++) {
                graph[i][j] = -1;
                minimum_spanning_tree[i][j] = -1;
            }
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

        create_mst();
        print();
    }


private:
    vector<vector<int>> graph; // Weighted graph
    vector<vector<int>> minimum_spanning_tree; // MST
    vector<bool> marked;
    int m_V;
    int total_weight;

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

    // Create Minimum Spanning Tree
    void create_mst() {
        for (int i = 0; i < m_V; i++) {
            if (graph[0][i] != -1) {
                total_weight += graph[0][i];
                minimum_spanning_tree[0][i] = graph[0][i];
                minimum_spanning_tree[i][0] = graph[i][0];
                marked[0] = true;
                marked[i] = true;
                break;
            }

        }

        while(!is_all_marked()) {
            int v = 0;
            int w = 0;
            find_lowest(&v, &w);
            visit(v, w);
        }

    }

    // Finds the vertex that is not connected and has the smallest weight.
    void find_lowest(int *v, int *w) {
        int min = -1;
        for (int i = 0; i < m_V; i++) {
            if (marked[i]) {
                for (int j = 0; j < m_V; j++) {
                    if ((!marked[j] && graph[i][j] != -1) && (min == -1 || min > graph[i][j])) {
                        *v = i;
                        *w = j;
                        min = graph[i][j];
                    }
                }
            }
        }
    }

    // Connects v and w
    void visit(int v, int w) {
        minimum_spanning_tree[v][w] = graph[v][w];
        minimum_spanning_tree[w][v] = graph[w][v];
        marked[v] = true;
        marked[w] = true;
        total_weight += minimum_spanning_tree[v][w];
    }

    // Checks if there are any vertex that is not connected
    bool is_all_marked() {
        for (int i = 0; i < m_V; i++) {
            if (!marked[i]) return false;
        }
        return true;
    }

    // Prints the result
    void print() {
        cout << "\n" << total_weight << endl;

        for (int i = 0; i < m_V; i++) {
            for (int j = m_V - 1; j >= 0; j--) {
                if(minimum_spanning_tree[i][j] != -1) {
                    cout << int_to_char(i) << " " << int_to_char(j) << endl;
                    minimum_spanning_tree[j][i] = -1;
                    minimum_spanning_tree[i][j] = -1;
                }
            }
        }
    }
};


int main() {
    MST mst = MST();
    return 0;
}