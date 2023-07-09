#include <bits/stdc++.h>
#include <vector>

using namespace std;

int main()
{
    int hole;
    cout << "Enter the number of free memory holes: ";
    cin >> hole;
    
    vector<int> holes(hole);
    cout << "Enter the size of each memory hole:\n";
    for (int i = 0; i < hole; i++)
    {
        cout << "Hole " << i+1 << ": ";
        cin >> holes[i];
    }

    int size;
    cout << "Enter the process size: ";
    cin >> size;

    sort(holes.begin(), holes.end());
    for (int x : holes)
    {
        if (x >= size)
        {
            cout << "The process is allocated into "
             << x << " MB memory hole.";
            return 0;
        }
    }
    cout << "No suitable hole available!";
    return 0;
}
