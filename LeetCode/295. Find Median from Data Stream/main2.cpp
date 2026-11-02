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
        lowerHalf.push(num);
        if(!upperHalf.empty() && lowerHalf.top() > upperHalf.top()) {
            int toDown = upperHalf.top();
            upperHalf.pop();
            int toUp = lowerHalf.top();
            lowerHalf.pop();
            upperHalf.push(toUp);
            lowerHalf.push(toDown);
        }
        if(lowerHalf.size() > n/2) {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
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
