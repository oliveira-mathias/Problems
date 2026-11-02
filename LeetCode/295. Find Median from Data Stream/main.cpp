class MedianFinder {
    // Max Heap
    priority_queue<int> lowerHalf;
    // Min Heap
    priority_queue<int, vector<int>, greater<int>> upperHalf;
    int n;
public:
    MedianFinder() : n(0) {}
    
    // Time: O(log(n))
    void addNum(int num) {
        n++;
        // Check in which half it needs to be inserted
        if(!lowerHalf.empty() && num < lowerHalf.top()) {
            // Here it goes in the lowerHalf container
            const int lowerHalfCapacity = n/2;
            int toStore = num;
            if(lowerHalf.size() >= lowerHalfCapacity) {
                // Here we move a number from the lowerHalf to the upperHalf
                int toMove = max(num, lowerHalf.top());
                toStore = min(num, lowerHalf.top());
                upperHalf.push(toMove);
                lowerHalf.pop();
            }
            lowerHalf.push(toStore);
        }
        else {
            // Here it goes in the upperHalf container
            const int upperHalfCapacity = n/2 + (n%2);
            int toStore = num;
            if(upperHalf.size() >= upperHalfCapacity) {
                // Here we move a member of upperHalf
                int toMove = min(num, upperHalf.top());
                toStore = max(num, upperHalf.top());
                lowerHalf.push(toMove);
                upperHalf.pop();
            }
            upperHalf.push(toStore);
        }
    }
    
    // Time: O(1)
    double findMedian() {
        if(n%2) {
            return upperHalf.top();
        }
        else {
            return (upperHalf.top() + lowerHalf.top())/2.0;
        }
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
