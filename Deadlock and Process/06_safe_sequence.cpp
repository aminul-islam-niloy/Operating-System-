#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Process {
    int pid;

    //allocated resource types 
    int type_a;
    int type_b;
    int type_c;
    //maximum resource types
    int max_type_a;
    int max_type_b;
    int max_type_c;
    ////need resource types
    int need_type_b;
    int need_type_c;
    int need_type_a;

    bool is_completed = false;
};

//available resources of each type
struct Resource {
    int type_a;
    int type_b;
    int type_c;
};

bool isSafeState(const Resource & r, const Process & p)
    {
        return (   p.need_type_a <= r.type_a 
                && p.need_type_b <= r.type_b 
                && p.need_type_c <= r.type_c);

                //if need <= avalable return true;
      }
// num of precess, resource and reference to the vector of processes
void Safe_Check(int n, Resource& r, vector<Process>& p) 
{
    int completed = 0;

    //store safe sequence
    vector<int> safe_sequence;

    while (completed != n)
     {
        bool is_deadlock = true;
        for (int i = 0; i < n; i++) 
        {
            if (!p[i].is_completed && isSafeState(r, p[i])) {
                p[i].is_completed = true;

                safe_sequence.push_back(p[i].pid); 
                completed++;
                
                //new or current avalable = avalable + allocation
                r.type_a += p[i].type_a;
                r.type_b += p[i].type_b;
                r.type_c += p[i].type_c;

                is_deadlock = false;
            }
        }

        if (is_deadlock) {
            cout << endl << "No Safe Sequence Found. Deadlock occur!";
            return;
        }
    }

    cout << endl << "Process in Safe state ! "<<endl;
    cout<<"Safe sequence is: ";
    for (int x : safe_sequence) {
        cout << x << " ";
    }
}

int main() {
    freopen("input_copy.txt", "r", stdin);

    int n;
    cout<<"from input file:"<<endl;
    //cout<<"Enter total process: ";
    cin >> n;
    //cout<<"Enter  avalable resource: ";
    Resource r;
    cin >> r.type_a >> r.type_b >> r.type_c;

    vector<Process> p(n);
    for (int i = 0; i < n; i++) 
    {
        cin >> p[i].type_a >> p[i].type_b >> p[i].type_c >> p[i].max_type_a >> p[i].max_type_b >> p[i].max_type_c;
        p[i].pid = i;

        //need = max - allocation

        p[i].need_type_a = p[i].max_type_a - p[i].type_a;
        p[i].need_type_b = p[i].max_type_b - p[i].type_b;
        p[i].need_type_c = p[i].max_type_c - p[i].type_c;
    }

    Safe_Check(n, r, p);
    return 0;
}

/*
5
3 3 2
0 1 0 7 5 3
2 0 0 3 2 2
3 0 2 9 0 2
2 1 1 2 2 2
0 0 2 4 3 3
*/