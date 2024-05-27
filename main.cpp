#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
using namespace std;

pair<vector<int>, int> bfs_tsp(const vector<vector<int>>& graph, int start);
pair<vector<int>, int> ucs_tsp(const vector<vector<int>>& graph, int start);
pair<vector<int>, int> a_star_tsp(const vector<vector<int>>& graph, int start);

// Function to generate a random graph for TSP
vector<vector<int>> generate_random_graph(int N) {
    vector<vector<int>> graph(N, vector<int>(N, 0));

    // Seed the random number generator
    srand(time(nullptr));

    // Generate random distances for the upper triangular part of the matrix
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            graph[i][j] = graph[j][i] = rand() % 100 + 1; // Random distance between 1 and 100
        }
    }

    // Set diagonal elements to 0
    for (int i = 0; i < N; ++i) {
        graph[i][i] = 0;
    }

    return graph;
}

int main() {
    // Define the distance matrix for the cities
    /*vector<vector<int>> graph = {
        {0, 29, 20, 21},
        {29, 0, 15, 17},
        {20, 15, 0, 28},
        {21, 17, 28, 0}
    };*/


    int N = 5; // Number of cities
    vector<vector<int>> graph = generate_random_graph(N);

    // Output the generated random graph
    cout << "Randomly generated graph:" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    int start = 0;  // Starting city

    // Run BFS for TSP
    auto [bfs_path, bfs_cost] = bfs_tsp(graph, start);

    // Run UCS for TSP
    auto [ucs_path, ucs_cost] = ucs_tsp(graph, start);

    // Run A* for TSP
    auto [a_star_path, a_star_cost] = a_star_tsp(graph, start);

    // Output the results of BFS
    cout << "BFS Path: ";
    for (int city : bfs_path) {
        cout << city << " ";
    }
    cout << "\nBFS Cost: " << bfs_cost << endl;

    // Output the results of UCS
    cout << "UCS Path: ";
    for (int city : ucs_path) {
        cout << city << " ";
    }
    cout << "\nUCS Cost: " << ucs_cost << endl;

    // Output the results of A*
    cout << "A* Path: ";
    for (int city : a_star_path) {
        cout << city << " ";
    }
    cout << "\nA* Cost: " << a_star_cost << endl;

    return 0;
}