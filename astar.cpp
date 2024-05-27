#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
#include <algorithm>

using namespace std;

// Node structure to store city information, path taken so far, cost, and heuristic cost
struct Node {
    int city;              // Current city
    vector<int> path;      // Path taken so far
    int cost;              // Cost incurred so far
    int heuristic_cost;    // Estimated cost to goal

    // Custom comparator to prioritize nodes with lower (cost + heuristic_cost)
    bool operator<(const Node& other) const {
        return (cost + heuristic_cost) > (other.cost + other.heuristic_cost);
    }
};

// Heuristic function to estimate remaining cost
int heuristic(int city, const vector<int>& path, const vector<vector<int>>& graph) {
    int min_cost = INT_MAX;

    // Iterate over the neighbors of the current city
    for (int neighbor = 0; neighbor < graph[city].size(); ++neighbor) {
        // Check if the neighbor is not in the path
        if (find(path.begin(), path.end(), neighbor) == path.end()) {
            // Update the minimum cost if the neighbor's cost is lower
            min_cost = min(min_cost, graph[city][neighbor]);
        }
    }

    // If there are no neighbors or all neighbors are already in the path, return 0
    return min_cost == INT_MAX ? 0 : min_cost;
}


// Function to perform A* search for TSP
pair<vector<int>, int> a_star_tsp(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    priority_queue<Node> pq;  // Priority queue for A*
    pq.push({ start, {start}, 0, heuristic(start, {start}, graph) });  // Start node

    int best_cost = INT_MAX;  // Initialize best cost to a large value
    vector<int> best_path;    // Initialize best path

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        // Check if all cities have been visited
        if (current.path.size() == n) {
            int total_cost = current.cost + graph[current.city][start];  // Return to start city
            if (total_cost < best_cost) {
                best_cost = total_cost;  // Update best cost
                best_path = current.path;
                best_path.push_back(start);  // Complete the tour
            }
            continue;
        }

        // Explore all unvisited cities
        for (int next_city = 0; next_city < n; ++next_city) {
            if (find(current.path.begin(), current.path.end(), next_city) == current.path.end()) {
                vector<int> new_path = current.path;
                new_path.push_back(next_city);
                int new_cost = current.cost + graph[current.city][next_city];
                pq.push({ next_city, new_path, new_cost, heuristic(next_city, new_path, graph) });
            }
        }
    }

    return { best_path, best_cost };
}
