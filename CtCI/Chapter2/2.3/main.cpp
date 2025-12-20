#include <algorithm>

template<class T>
struct Node {
  Node* next;
  T val;
};

template<class T>
void deleteMiddleNode(Node<T>* node) {
  Node<T>* next = node->next;
  // By hypothesis next is non null
  std::swap(node->val, next->val);
  node->next = next->next;
  delete next;
}

int main() {
}
