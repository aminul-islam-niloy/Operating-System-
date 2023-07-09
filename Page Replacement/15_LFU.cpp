#include<bits/stdc++.h>
using namespace std;

int page_fault_finder(const vector<int>& pages, int frame) 
{
    unordered_map<int, int> pageCount;  // Map to track page frequencies
    unordered_map<int, int> pageFrame;  // Map to track page positions in frames
    priority_queue<pair<int, int>, vector<pair<int, int>>,
    greater<pair<int, int>>> prio_que;  // Priority queue to track least frequently used pages
   
    int page_faults = 0;

    for (int page : pages) {

        //hecks whether a given page is present in the pageFrame unordered map
        if (pageFrame.find(page) != pageFrame.end())
         {
            // Page already exists in the frame
            pageCount[page]++;
        } else
         {
            // Page is not present in the frame
            page_faults++;

            if (pageFrame.size() == frame) {
                // Frame is full, need to replace a page
                while (!prio_que.empty() && pageFrame.find(prio_que.top().second) == pageFrame.end()) {
                    // Remove pages from priority queue that are no longer in the frame
                    prio_que.pop();
                }

                if (!prio_que.empty()) {
                    // Replace the least frequently used page from the frame
                    int leastFrequentPage = prio_que.top().second;
                    prio_que.pop();
                    pageFrame.erase(leastFrequentPage);
                    pageCount.erase(leastFrequentPage);
                }
            }

            // Insert the new page into the frame and update the data structures
            pageFrame[page] = 1; //page is now present in the frame
            pageCount[page] = 1; //page has been accessed once, as it caused a page fault
            prio_que.push({ pageCount[page], page });
           // the frequency of the page (obtained from pageCount[page]) 
           //and the page number itself.  keep track of the 
           //least frequently used pages in the priority queue.
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

// 10 3      4 7 6 1 7 6 1 2 7 2 --->5



