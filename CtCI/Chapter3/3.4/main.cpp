#include<stack>

using namespace std;

class MyQueue {
  stack<int> in_queue, out_queue;

  void transferQueue() {
    while(!in_queue.empty()) {
      out_queue.push(in_queue.top());
      in_queue.pop();
    }
  }

  public:
  void enqueue(int val) {
    in_queue.push(val);
  }

  int front() {
    if(out_queue.empty()) {
      transferQueue();
    }

    if(out_queue.empty()) {
      throw "Empty Queue";
    }

    return out_queue.top();
  }

  void dequeue() {
    if(out_queue.empty()) {
      transferQueue();
    }

    if(out_queue.empty()) {
      throw "Empty Queue";
    }

    out_queue.pop();
  }
};
