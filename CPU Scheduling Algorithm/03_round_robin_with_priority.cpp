#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int remainingTime;
};

int main() {
    int n, quantum;
    cout << "Enter total number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    vector<int> CT(n), TAT(n), WT(n);

    cout << "Enter process IDs: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].id;
    }

    cout << "Enter arrival time: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].arrivalTime;
    }

    cout << "Enter burst time: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].burstTime;
    }

    cout << "Enter priority: ";
    for (int i = 0; i < n; i++) {
        cin >> processes[i].priority;
    }

    cout << "Enter time quantum: ";
    cin >> quantum;

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remainingTime = processes[i].burstTime;
    }

    int currentTime = 0;
    bool completed = false;
    int completedProcesses = 0;

    // Priority queue for processes based on arrival time and priority
    auto compare = [](const Process& p1, const Process& p2) {
        if (p1.arrivalTime == p2.arrivalTime) {
            return p1.priority > p2.priority;
        }
        return p1.arrivalTime > p2.arrivalTime;
    };
    priority_queue<Process, vector<Process>, decltype(compare)> pq(compare);

    // Add processes to the priority queue
    for (int i = 0; i < n; i++) {
        pq.push(processes[i]);
    }

    // Perform Round Robin scheduling with priority
    while (completedProcesses < n) {
        Process currentProcess = pq.top();
        pq.pop();

        if (currentProcess.remainingTime > 0) {
            completed = false;

            if (currentProcess.remainingTime > quantum) {
                currentTime += quantum;
                currentProcess.remainingTime -= quantum;
            } else {
                currentTime += currentProcess.remainingTime;
                currentProcess.remainingTime = 0;
                WT[currentProcess.id] = currentTime - currentProcess.arrivalTime - currentProcess.burstTime;
                CT[currentProcess.id] = currentTime;
                completedProcesses++;
            }

            // Check for newly arrived processes
            while (completedProcesses < n && processes[completedProcesses].arrivalTime <= currentTime) {
                pq.push(processes[completedProcesses]);
                completedProcesses++;
            }

            pq.push(currentProcess);
        }

        if (completed) {
            break;
        }
    }

    float awt = 0, atat = 0, act = 0;

    // Calculate turnaround time and total waiting time
    for (int i = 0; i < n; i++) {
        TAT[i] = CT[i] - processes[i].arrivalTime;
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
