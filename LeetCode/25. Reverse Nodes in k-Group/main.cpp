/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while(curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode sentinel(0, head);
        ListNode* prev = &sentinel;
        ListNode* curr = head;

        while(curr) {
            int nodeCount;
            // curr is included in the count
            for(nodeCount=1; curr->next && nodeCount<k; nodeCount++) {
                curr = curr->next;
            }
            // CHeck if there are enough nodes
            if(nodeCount < k) {
                break;
            }

            ListNode* subListStart = prev->next;
            ListNode* subListEnd = curr;
            ListNode* nextNode = subListEnd->next;

            // Reverse sublist
            subListEnd->next = nullptr;
            reverseList(subListStart);

            // Fix the list
            prev->next = subListEnd;
            subListStart->next = nextNode;

            //  Updating the pointers
            prev = subListStart;
            curr = nextNode;
        }

        return sentinel.next;
    }
};
