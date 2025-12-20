/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
    int listSize(ListNode* head) {
        int size = 0;
        while(head) {
            size++;
            head = head->next;
        }
        return size; 
    }
public:
    // Time: O(N + M)
    // Space: O(1)
    ListNode* getIntersectionNode(ListNode *headA, ListNode *headB) {
        // Edge case
        if(!headA || !headB) return nullptr;

        // Normalizing the lists
        int size1 = listSize(headA);
        int size2 = listSize(headB);
        while(size1 != size2) {
            if(size1 > size2) {
                --size1;
                headA = headA->next;
            }
            else {
                --size2;
                headB = headB->next;
            }
        }

        // Searching for the intersection
        int l = 0;
        int r = size1 + 1; // We contemplate the nullptr at the end of the list
        while(l < r) {
            int m = l + (r-l)/2;

            ListNode* aux1 = headA;
            ListNode* aux2 = headB;
            for(int i=l; i<m; ++i) {
                aux1 = aux1->next;
                aux2 = aux2->next;
            }

            if(aux1 == aux2) {
                r = m;
            }
            else {
                l = m + 1;
                headA = aux1->next;
                headB = aux2->next;
            }
        }

        return headA;
    }
};
