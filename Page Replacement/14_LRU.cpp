#include<bits/stdc++.h>
using namespace std;

int page_fault_finder(const vector<int>& pages, int frame) {
    unordered_set<int> s;  // Set to track unique pages in frames
    deque<int> dq;  // Deque to maintain order of pages
   
    int page_faults = 0;

    for (int page : pages) {
        if (s.size() < frame) {
            // If there is space in the frames
            if (s.find(page) == s.end()) {
                // Page fault occurs if the page is not already in the frames
                page_faults++;
                s.insert(page);
                dq.push_back(page);
            }
        } 
        else {
            // If there is no space in the frames
            if (s.find(page) == s.end()) {
                // Page fault occurs if the page is not already in the frames
                int least_recent = dq.front();
                dq.pop_front();
                s.erase(least_recent);

                page_faults++;
                s.insert(page);
                dq.push_back(page);
            } else {
                // Page is already in the frames
                // Move the page to the end of the deque to update its recent usage
                dq.erase(remove(dq.begin(), dq.end(), page), dq.end());
                dq.push_back(page);
            }
        }
    }
    
    return page_faults;
}

int main() {
    int n, frameNo, pageFaults;
    cout << "Enter the length of the reference string: ";
    cin >> n;

    vector<int> pages(n);
    cout << "Enter the reference string: ";
    for (int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter the number of frames: ";
    cin >> frameNo;

    // Call the page_fault_finder function to get the total page faults
    pageFaults = page_fault_finder(pages, frameNo);
    cout << "Total page faults: " << pageFaults << endl;

    return 0;
}


