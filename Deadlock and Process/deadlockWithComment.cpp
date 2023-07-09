#include <iostream>
#include <vector>

using namespace std;

// Function to check for cycles starting from a given node
bool haveCycle(int current_node, vector<bool>& visited, vector<vector<int>>& graph) {
    visited[current_node] = true;  // Mark the current node as visited

    // Explore all neighbors of the current node
    for (int x : graph[current_node]) {
        if (!visited[x]) {
            // If the neighbor 'x' is not visited, recursively check for cycles starting from 'x'
            if (haveCycle(x, visited, graph))
                return true;  // If a cycle is found in the recursion, return true
        } else {
            return true;  // If the neighbor 'x' has already been visited, a cycle is detected
        }
    }

    visited[current_node] = false;  // Current node is no longer part of the current path
    return false;  // No cycle found starting from the current node
}

int main() {
    freopen("input.txt", "r", stdin);  // Redirect standard input to read from a file named "input.txt"

    int n, m;
    cin >> n >> m;  // Read the number of nodes and edges in the graph

    vector<bool> visited(n + 1, false);  // Create a boolean vector to track visited nodes
    vector<vector<int>> graph(n + 1);  // Create an adjacency list to represent the graph

    // Read the edges and construct the graph
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);  // Add edge 'a' -> 'b' to the adjacency list
    }

    bool hasDeadlock = false;  // Flag to indicate if a deadlock is found

    // Check for cycles starting from each unvisited node
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && haveCycle(i, visited, graph)) {
            hasDeadlock = true;  // If a cycle is found, set the deadlock flag and break the loop
            break;
        }
    }

    // Print the result based on the presence of a deadlock
    if (hasDeadlock)
        cout << "Deadlock Found!" << endl;
    else
        cout << "No Deadlock Found" << endl;

    return 0;
}
