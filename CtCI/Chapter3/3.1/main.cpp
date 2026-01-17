#include <cassert>
#include <cstring>
#include <vector>

using namespace std;

template<class T, unsigned N>
class NStack {
  vector<T> s; // element container
  vector<int> head; // start pos of the stack
  vector<int> tail; // current write pos
  const int increaseFactor = 2;

  private:
  void resize() {
    vector<T> newStack;
    newStack.resize(increaseFactor*s.size());
    int newCapacity = newStack.size()/N;

    // Copying elements
    for(int i=0; i<N; i++) {
      int newHead = i*newCapacity;
      int size = tail[i] - head[i];
      for(int j=0; j<size; ++j) {
        newStack[newHead + j] = move(s[head[i] + j]);
      }
    }

    swap(newStack, s);

    // Fixing head and tail
    for(int i=0; i<N; ++i) {
      int size = tail[i]-head[i];
      head[i] = i*newCapacity;
      tail[i] = head[i] + size;
    }
    head[N] = s.size();

  }

  public:
  NStack() {
    s.resize(N);
    tail.resize(N);
    head.resize(N + 1);

    for(int i=0; i<N; ++i) {
      head[i] = i;
      tail[i] = i;
    }

    head[N] = N;
  }

  void Push(const T& elem, unsigned pos) {
    assert(pos <= N && pos > 0);
    // Check for resize
    if(tail[pos-1]==head[pos]) {
      resize();
    }

    s[tail[pos-1]] = elem;
    tail[pos-1]++;
  }

  void Pop(unsigned pos) {
    assert(pos <= N && pos > 0);
    int stackSize = tail[pos-1] - head[pos-1];
    assert(stackSize > 0);
    tail[pos-1]--;
  }

  T Peek(unsigned pos) {
    assert(pos <= N && pos > 0);
    int stackSize = tail[pos-1] - head[pos-1];
    assert(stackSize > 0);

    return s[tail[pos-1]-1];
  }
};

int main() {
}
