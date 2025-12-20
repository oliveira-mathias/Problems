Node* kthToLast(Node* head, int k) {
  Node* r = head;
  Node* l = head;

  // Positionate r
  int i;
  for (i=0; i<k && r; ++i) {
    r = r->next;
  }

  // Handling the case where k is larger than the list
  if(i < k) return nullptr;

  // Positionate l
  while(r) {
    r = r->next;
    l = l->next;
  }

  return l;
}
