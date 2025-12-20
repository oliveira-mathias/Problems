struct Node {
  Node* next;
  int val;
  Node() {}
  Node(int  num) : val(num), next(nullptr) {}
};

Node* addNumbersReversed(Node* n1, Node* n2) {
  Node sum;
  Node* sumTail = &sum;
  int carry = 0;

  while(n1 || n2 || carry) {
    sumTail->next = new Node(0);
    sumTail = sumTail->next;

    if(n1) {
      sumTail->val += n1->val;
      n1 = n1->next;
    }

    if(n2) {
      sumTail->val += n2->val;
      n2 = n2->next;
    }

    sumTail->val += carry;

    carry = sumTail->val/10;
    sumTail->val %= 10;

  }

  return sum.next;
}

Node* reverseList(Node* head) {
  Node* prev = nullptr;
  Node* curr = head;
  Node* next = nullptr;
  while(curr) {
    next = curr->next;
    curr->next = prev;

    prev = curr;
    curr = next;
  }

  return prev;
}

Node* sumList(Node*n1, Node* n2) {
  n1 = reverseList(n1);
  n2 = reverseList(n2);
  Node* sum = addNumbersReversed(n1, n2);
  n1 = reverseList(n1);
  n2 = reverseList(n2);
  return reverseList(sum);
}
