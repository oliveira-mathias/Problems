void reverseStack(stack<int>& s) {
  stack<int> aux;

  while(!s.empty()) {
    aux.push(s.top());
    s.pop();
  }

  s = move(aux);
}

stack<int> mergeStacks(stack<int>& s1, stack<int>& s2) {
  stack<int> res;

  while(!s1.empty() || !s2.empty()) {
    int minElement = numeric_limits<int>::max();
    bool s1HasMin = false;

    if(!s1.empty()) {
      minElement = s1.top();
      s1HasMin = true;
    }

    if(!s2.empty() && s2.top() < minElement) {
      minElement = s2.top();
      s1HasMin = false;
    }

    if(s1HasMin) {
      s1.pop();
    }
    else {
      s2.pop();
    }

    res.push(minElement);
  }

  return res;
}

stack<int> mergeStackSortRec(stack<int>& s) {
  if(s.empty()) return s;

  stack<int> s1, s2;

  while(!s.empty()) {
    s1.push(s.top());
    s.pop();

    if(!s.empty()) {
      s2.push(s.top());
      s.pop();
    }
  }

  // Base case
  // We are checking if s.size() == 1
  if(s2.empty()) return s1;

  s1 = move(mergeStackSortRec(s1));
  s2 = move(mergeStackSortRec(s2));

  s = mergeStacks(s1, s2);
  reverseStack(s);

  return s;

}

// Time: O(n log(n))
// Space: O(n)
void mergeStackSort(stack<int>& stack) {
  stack = move(mergeStackSortRec(stack));
}
