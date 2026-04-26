class MinStack {
  std::vector<int> s;
  std::vector<int> minStack;

  public:
  void push(int elem) {
    if(minStack.empty() || (minStack.back() >= elem)) {
      minStack.push_back(elem);
    } 

    s.push_back(elem);
  }

  void pop() {
    if(s.empty()) throw "Empty stack";
    
    if(s.back() == minStack.back()) {
      minStack.pop_back();
    }

    s.pop_back();
  }

  int top() {
    if(s.empty()) throw "Empty stack";
    return s.back();
  }

  int min() {
    if(s.empty()) throw "Empty stack";
    return minStack.back();
  }
};
