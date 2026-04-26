template<int N>
class SetOfStacks {
  vector<vector<int>> s;

  void removeEmptySuffix() {
    while(!s.empty() && s.back().empty()) {
      s.pop_back();
    }
  }

  public:
  SetOfStacks() {
    if(N <= 0) {
      throw "Invalid Template Parameter;"
    }
  }

  void push(int val) {
    removeEmptySuffix();
    if(s.empty() || s.back().size() >= N) {  
      s.emplace_back(vector<int>());
      s.back().reserve(N);
    }
    s.back().push_back(val);
  }

  int top() {
    removeEmptySuffix();
    if(s.empty()) {
      throw "Invalid Stack Access";
    }

    return s.back().back();
  }

  void pop() {
    removeEmptySuffix();
    
    if(s.empty()) {
      throw "Invalid Stack Pop";
    }

    s.back().pop_back();
    
    removeEmptySuffix();
  }

  void popAt(int idx) {
    if(idx >= s.size() || s[idx].empty()) {
      throw "Invalid Stack Index";
    }

    s[idx].pop_back();
  }
};
