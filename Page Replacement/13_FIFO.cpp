#include<bits/stdc++.h>
using namespace std;

int page_fault_finder(const vector<int>& pages, int frame) {
    unordered_set<int> s;  // Set to track unique pages in frames
    queue<int> q;  // Queue to maintain order of pages
   
    int page_faults = 0;

    for (int page : pages) {
        if (s.size() < frame) {

            // If the page is not already in the frame

            //he page is inserted into the set s, and its
            // position in the reference string is added to 
            //the queue q. The page_faults counter is incremented.

            if (s.find(page) == s.end()) {
                page_faults++;
                s.insert(page);
                q.push(page);
            }
        } 
        else {

//The least recently used page, which is at the front of the queue q,
// is removed from the frames by popping it from the queue and erasing 
//it from the set s. The new page is then inserted into the set s,
// and its position in the reference string is added to the queue q.
// The page_faults counter is incremented.
           
            if (s.find(page) == s.end()) 
            {
                int first = q.front();
                q.pop();
                s.erase(first);

                page_faults++; // process is not in frame
                s.insert(page);
                q.push(page);
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

    pageFaults = page_fault_finder(pages, frameNo);
    cout << "Total page faults: " << pageFaults << endl;

    return 0;
}
