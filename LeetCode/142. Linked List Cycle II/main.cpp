/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if(!head) return nullptr;

        ListNode* p1 = head;
        ListNode* p2 = head;

        // Search for the cycle
        while(p2) {
            p1 = p1->next;
            p2 = p2->next;

            if(p2) {
                p2 = p2->next;
            }
            else {
                // Here the list ended
                return nullptr;
            }

            if(p1 == p2) {
                break;
            }
        }

        // We make sure we have a p2 in the list
        if(!p2) {
            return nullptr;
        }

        // Search for the enter point of the cycle
        p1 = head;
        while(p1 != p2) {
            p1 = p1->next;
            p2 = p2->next;
        }

        return p1;
    }
};
