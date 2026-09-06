/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    Node* copyRandomList(Node* head) {
        if(!head) return nullptr;

        // First pass, duplicate the list
        for(Node* curr = head; curr!=nullptr;) {
            Node* copyCurr = new Node(curr->val);
            copyCurr->next = curr->next;
            curr->next = copyCurr;
            curr = copyCurr->next;
        }

        // Second pass, we resolve the random nodes
        for(Node* curr=head; curr!=nullptr;) {
            Node* currCopy = curr->next;
            if(curr->random) {
                currCopy->random = curr->random->next;
            }
            curr = currCopy->next;
        }

        // Thir pass separate the lists
        Node sentinel(0);
        Node* insertPoint = &sentinel;
        for(Node* curr=head; curr!=nullptr; curr=curr->next) {
            Node* currCopy = curr->next;
            insertPoint->next = currCopy;
            curr->next = currCopy->next;
            insertPoint = insertPoint->next;
        }

        return sentinel.next;
    }
};
