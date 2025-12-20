struct Node {
  Node* next;
  int val;
};

Node* reverseList(Node* head) {
  Node* prev = nullptr;
  Node* curr = head;

  while(curr) {
    Node* next = curr->next;
    
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  return prev;
}

bool isPalindrome(Node* head) {
  // Edge cases
  if(!head || !head->next) {
    return true;
  }

  // Split the list in halves
  Node* prev = nullptr;
  Node* slow = head;
  Node* fast = head;

  while(fast) {
    prev = slow;
    slow = slow->next;
    fast = fast->next;
    if(fast) {
      fast = fast->next;
    }
  }

  prev->next = nullptr;

  // Do the comparision
  slow = reverseList(slow);

  bool result = true;
  Node* head1 = head;
  Node* head2 = slow;
  while(head1 && head2) {
    if(head1->val != head2->val) {
      result = false;
      break;
    }
    head1 = head1->next;
    head2 = head2->next;
  }

  // We fix the original list
  slow = reverseList(slow);
  prev->next = slow;
  return result;
}

int main() {}
