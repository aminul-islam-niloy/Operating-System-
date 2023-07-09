#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    cout << "Enter total number of processes: ";
    cin >> n;

    vector<int> P(n), A(n), B(n), Priority(n);
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

    cout << "Enter priority: ";
    for (int i = 0; i < n; i++) {
        cin >> Priority[i];
    }

    // Sort the processes based on their priority in ascending order
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) 
        {
            if (Priority[j] > Priority[j + 1])
             {
                swap(P[j], P[j + 1]);
                swap(A[j], A[j + 1]);
                swap(B[j], B[j + 1]);
                swap(Priority[j], Priority[j + 1]);
            }
        }
    }

    //   // Sort the processes based on their priority in descending order
    // for (int i = 0; i < n - 1; i++) {
    //     for (int j = 0; j < n - i - 1; j++) {
    //         if (Priority[j] < Priority[j + 1]) {
    //             swap(P[j], P[j + 1]);
    //             swap(A[j], A[j + 1]);
    //             swap(B[j], B[j + 1]);
    //             swap(Priority[j], Priority[j + 1]);
    //         }
    //     }
    // }


    // Calculate completion time
    for (int i = 0; i < n; i++) {
        CT[i] = B[i];
        for (int j = 0; j < i; j++) {
            CT[i] += B[j];
        }
    }

    float awt = 0, atat = 0, act = 0;

    // Calculate table
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - A[i];
        atat += TAT[i];
        WT[i] = TAT[i] - B[i];
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
