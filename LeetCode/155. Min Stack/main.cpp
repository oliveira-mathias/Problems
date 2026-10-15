class MinStack {
    vector<int> s;
    vector<pair<int, int>> minDP;
    
    public:
    MinStack() {}
    
    void push(int value) {
        s.push_back(value);

        int currMin = numeric_limits<int>::max();
        if(!minDP.empty()) {
            currMin = minDP.back().first;
        }
        if(minDP.empty() || value < currMin) {
            minDP.push_back({value, 1});
        }
        else if(value == currMin) {
            minDP.back().second++;
        }
    }
    
    void pop() {
        // Stack should not be empty
        assert(!s.empty());
        if(s.empty()) return;

        int lastElement = s.back();
        int currMin = minDP.back().first;

        s.pop_back();
        if(lastElement == currMin) {
            minDP.back().second--;
            if(!minDP.back().second) {
                minDP.pop_back();
            }
        }
    }
    
    int top() {
        // Stack should not be empty
        assert(!s.empty());
        if(s.empty()) throw "Invalid top operation";

        return s.back();
    }
    
    int getMin() {
        // Stack should not be empty
        assert(!s.empty());
        if(s.empty()) throw "Invalid getMin operation";

        return minDP.back().first;
    }
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(value);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
