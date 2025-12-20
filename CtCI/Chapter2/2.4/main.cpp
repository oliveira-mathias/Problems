struct Node {
  Node* next;
  int val;

  Node() : next(nullptr), val(0) {}
};

Node* partition(Node* head, int x) {
  Node sentinel;
  sentinel.next = head;
  Node lessX;
  Node* lessXTail = &lessX;

  for(Node* aux = &sentinel; aux->next;) {
    if(aux->next->val < x) {
      lessXTail->next = aux->next;
      lessXTail = lessXTail->next;
      aux->next = aux->next->next;
      lessXTail->next = nullptr;
    }
    else {
      aux = aux->next;
    }
  }

  lessXTail->next = sentinel.next;
  return lessX.next;
}

int main() {
}
