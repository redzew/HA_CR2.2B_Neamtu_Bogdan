#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <tuple>
#include <algorithm>

using namespace std;

// Node structure to store city information, path taken so far, and cost
struct Node {
    int city;              // Current city
    vector<int> path;      // Path taken so far
    int cost;              // Cost incurred so far

    // Custom comparator to prioritize nodes with lower cost
    bool operator<(const Node& other) const {
        return cost > other.cost;
    }
};

// Function to perform BFS for TSP
pair<vector<int>, int> bfs_tsp(const vector<vector<int>>& graph, int start) {
    int n = graph.size();
    queue<Node> q;  // Queue for BFS
    q.push({ start, {start}, 0 });  // Start node

    int best_cost = INT_MAX;  // Initialize best cost to a large value
    vector<int> best_path;    // Initialize best path

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

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
                q.push({ next_city, new_path, current.cost + graph[current.city][next_city] });
            }
        }
    }

    return { best_path, best_cost };
}
