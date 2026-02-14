// Could also have used the linked list approach
#include <iostream>
#include <utility>

template<class T, int N=3>
class NStack {
  T* s;
  int* head;
  int* tail;
  int size;

  public:
  NStack() {
    s = new T[N];
    head = new int[N+1];
    tail = new int[N];
    size = N;

    for(int i=0; i<N; ++i) {
      head[i] = i;
      tail[i] = i;
    }

    head[N] = N;
  }

  ~NStack() {
    delete[] s;
    delete[] head;
    delete[] tail;
  }

  void push(T elem, int idx) {
    if(idx < 0 || idx >= N) throw "Invalid Stack Index";

    // Allocating more space
    if(tail[idx] == head[idx+1]) {
      // New stack
      T* aux = new T[size + 1];

      // Copy the prefix
      for(int i=0; i<head[idx+1]; ++i) {
        aux[i] = std::move(s[i]);
      }

      // Copy the suffix
      for(int i=head[idx+1]; i<size; ++i) {
        aux[i+1] = std::move(s[i]);
      }

      // Adjusting heads
      for(int i=idx+1; i<N; ++i) {
        head[i]++;
        tail[i]++;
      }
      head[N]++;

      // Releasing old stack
      delete[] s;

      s = aux;
      size++;
      aux = nullptr;
    }

    s[tail[idx]] = std::move(elem);
    tail[idx]++;
  }

  void pop(int idx) {
    if(idx < 0 || idx >= N) throw "Invalid Stack Index";

    // Empty stack
    if(tail[idx] <= head[idx]) throw "Empty stack";

    tail[idx]--;
  }

  T& top(int idx) {
    if(idx < 0 || idx >= N) throw "Invalid Stack Index";

    // Empty stack
    if(tail[idx] <= head[idx]) throw "Empty stack";

    return s[tail[idx]-1];
  }

};


int main() {
  NStack<int, 3> s;

  s.print();
  s.push(7, 0);
  s.print();
  s.push(1, 0);
  s.print();
  s.push(5, 2);
  s.print();
  s.push(9, 1);
  s.print();

  std::cout << s.top(0) << std::endl;
  std::cout << s.top(2) << std::endl;
  s.pop(0);
  std::cout << s.top(0) << std::endl;
  std::cout << s.top(1) << std::endl;
  s.push(2, 1);
  s.print();
  std::cout << s.top(1) << std::endl;
}
