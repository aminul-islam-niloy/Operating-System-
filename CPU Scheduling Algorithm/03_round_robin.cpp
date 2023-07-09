#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, quantum;
    cout << "Enter total number of processes: ";
    cin >> n;

    vector<int> P(n), A(n), B(n);
    vector<int> CT(n), TAT(n), WT(n);

    cout << "Enter process IDs: ";
    for (int i = 0; i < n; i++) {
        cin >> P[i];
    }

    cout << "Enter arrival time: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    cout << "Enter burst time: ";
    for (int i = 0; i < n; i++) {
        cin >> B[i];
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    int remainingTime[n];
    for (int i = 0; i < n; i++) {
        remainingTime[i] = B[i];
    }

    int currentTime = 0;
    bool completed = false;

    // Perform Round Robin scheduling
    while (!completed) {
        completed = true;
        for (int i = 0; i < n; i++) {
            if (remainingTime[i] > 0) {
                completed = false;
                if (remainingTime[i] > quantum) {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                } else {
                    currentTime += remainingTime[i];
                    WT[i] = currentTime - A[i] - B[i];
                    remainingTime[i] = 0;
                    CT[i] = currentTime;
                }
            }
        }
    }

    float awt = 0, atat = 0, act = 0;

    // Calculate turnaround time and total waiting time
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - A[i];
        atat += TAT[i];
        awt += WT[i];
        act += CT[i];
    }

    cout << endl;

    cout << "Completion time: ";
    for (int g : CT) {
        cout << g << " ";
    }
    cout << endl;

    cout << "Turnaround time: ";
    for (int t : TAT) {
        cout << t << " ";
    }
    cout << endl;

    cout << "Waiting time: ";
    for (int i = 0; i < n; i++) {
        cout << WT[i] << " ";
    }
    cout << endl;

    cout << "Average waiting time: " << awt / n << endl;
    cout << "Average completion time: " << act / n << endl;
    cout << "Average turnaround time: " << atat / n << endl;

    return 0;
}
