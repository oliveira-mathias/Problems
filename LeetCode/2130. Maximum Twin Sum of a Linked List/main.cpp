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
public:
    // Time: O(n)
    // Space: O(1)
    int pairSum(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while(fast) {
            slow = slow->next;
            fast = fast->next;
            if(fast) fast = fast->next;
        }

        // Here slow is the head of the twin list
        auto reverse = [](ListNode* head) -> ListNode* {
            ListNode* prev = nullptr;
            ListNode* current = head;
            while(current) {
                ListNode* next = current->next;
                current->next = prev;
                prev = current;
                current = next;
            }
            return prev;
        };
        ListNode* revHead = reverse(slow);
        ListNode* aux = revHead;
        int maxSum = numeric_limits<int>::min();
        while(aux && head) {
            maxSum = max(maxSum, head->val + aux->val);
            head = head->next;
            aux = aux->next;
        }
        reverse(revHead);
        return maxSum;
    }
};
