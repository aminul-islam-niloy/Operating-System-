#include <iostream>
#include <vector>

using namespace std;

bool haveCycle(int current_node, vector<bool>& visited, vector<vector<int>>& graph) {
    visited[current_node] = true;
    for (int x : graph[current_node]) {
        if (!visited[x]) {
            if (haveCycle(x, visited, graph))
                return true;  //if x already visited then circle
        } else {
            return true; //neighbor x has already been visited,  a cycle is detected
        }
    }
    visited[current_node] = false; //current node is no longer part of the current path
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    vector<bool> visited(n + 1, false);
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
    }

    bool hasDeadlock = false;
    for (int i = 1; i <= n; i++) {
        if (!visited[i] && haveCycle(i, visited, graph)) {
            hasDeadlock = true;
            break;
        }
    }

    if (hasDeadlock)
        cout << "Deadlock Found!" << endl;
    else
        cout << "No Deadlock Found" << endl;

    return 0;
}
