struct Node {
  int data;
  Node* next;
};

bool contains(Node* head, int item) {
  while(head) {
    if(head->data == item) {
      return true;
    }
    head = head->next;
  }

  return false;
}

Node* removeDups(Node* head) {
  Node* prev = nullptr;
  Node* curr = head;

  Node* newHead = head;
  while (curr) {
    if (contains(curr->next, curr->data)) {
      Node* next = curr->next;
      if (prev) {
        prev->next = next;
      }
      // Here we are deleting the head
      else {
        newHead = next;
      }
      delete curr;
      curr = next;
    }
    else {
      prev = curr;
      curr = curr->next;
    }
  }

  return newHead;
}

int main() {}
