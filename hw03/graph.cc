/*
 * Yasar Polatli 250201075
 */

#include "graph.hpp"

#include <iostream>
#include <iomanip>
#include <queue>

using namespace std;

GraphAdjMat::GraphAdjMat(int V)
        : m_V(V), m_E(0) {
    // Resize 2 dimensional vector and initialize
    matrix.resize(V);
    for (int i = 0; i < V; i++) {
        matrix[i].resize(V);
        for (int j = 0; j < V; j++)
            matrix[i][j] = 0;
    }
}

GraphAdjMat::~GraphAdjMat() {
    for (int i = 0; i < V(); ++i) {
        for (int j = 0; j < V(); j++)
            matrix[i][j] = 0;
    }
}

void GraphAdjMat::insert(int v, int w) {
    // check for valid vertex ids, they must be in the range [0, V-1]
    if (v >= V() || w >= V() || v < 0 || w < 0) {
        cerr << "Error: vertex indices for insertion must be in the range [0, " << (V() - 1) << "]!" << endl;
        return;
    }

    // Check for self loops, do not allow for simple graphs.
    if (v == w) {
        cerr << "Error: skipping self loop insertion!" << endl;
        return;
    }

    // Add edges to the matrix
    matrix[v][w] = 1;
    matrix[w][v] = 1;

    m_E++;
}


void GraphAdjMat::print() const {
    cout << "V = " << V() << ", E = " << E() << endl;
    // For each vertex, print the vertex id and the list of adjacent vertices

    for (int i = 0; i < V(); i++) {
        cout << setw(3) << i << ": ";
        for (int j = V() - 1; j >= 0; j--) {
            if (matrix[i][j] == 1)
                cout << j << " ";
        }
        cout << endl;
    }

}


int GraphAdjMat::shortest_path(int src, int dst, std::stack<int> &path) {
    queue<int> bfs_queue;
    vector<bool> marked(V(), false);
    vector<int> edge_to(V(), -1);

    // mark source and add it to the queue
    marked[src] = true;
    bfs_queue.push(src);

    while (!bfs_queue.empty()) {
        // while queue not empty, check each item on top
        int n = bfs_queue.front();
        bfs_queue.pop();

        // go through the edges of the top item in the queue, n.
        for (int i = V() - 1; i >= 0; i--) {
            if (matrix[n][i] == 1) {
                // if it is not marked as reachable from source, then
                // mark it an add it as on the shortest path toward
                // source in the direction of n
                if (!marked[i]) {
                    edge_to[i] = n;
                    marked[i] = true;
                    bfs_queue.push(i);
                }
            }
        }
    }

    // clear stack
    while (!path.empty())
        path.pop();

    // if there is no path to destination return -1
    if (!marked[dst])
        return -1;

    // push nodes starting from destination onto the stack by following the
    // marked shortest path edges
    for (int n = dst; n != src; n = edge_to[n])
        path.push(n);
    // add source to complete path
    path.push(src);

    // return number of nodes in the path
    return path.size();
}

int GraphAdjMat::connected_components(std::vector<int> &ids) {
    ids.resize(V());
    if (V() == 0)
        return 0;

    // initially all vertices are unmarked and the initial connected
    // component id is zero.
    vector<bool> marked(V(), false);
    int cc_id = 0;

    queue<int> bfs_queue;
    for (int i = 0; i < V(); ++i) {
        // start a BFS from each unmarked vertex
        if (!marked[i]) {
            bfs_queue.push(i);
            while (!bfs_queue.empty()) {
                int n = bfs_queue.front();
                bfs_queue.pop();
                // as we pop items from the queue, label their
                // ids with the current connected component id.
                ids[n] = cc_id;

                for (int j = V() - 1; j >= 0; j--) {
                    if (matrix[n][j] == 1) {
                        if (!marked[j]) {
                            marked[j] = true;
                            bfs_queue.push(j);
                        }
                    }
                }
            }

            // End of BFS. Increase connected component id.
            ++cc_id;
        }
    }

    // number of components is the value of id at the end
    return cc_id;
}
