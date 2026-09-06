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
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
        if(!head) return vector<int>({-1, -1});

        ListNode* prev = head;
        ListNode* curr = prev->next;

        int i = 1;
        int firstCriticalPoint = -1;
        int currCriticalPoint = -1;
        int minDist = numeric_limits<int>::max();
        const auto isCriticalPoint = [](int prev, int curr, int next) {
            return ((curr > prev) && (curr > next)) || ((curr < prev) && (curr < next));
        };
        for(;curr && curr->next; prev=prev->next, curr=curr->next, i++) {
            ListNode* next = curr->next;
            if(isCriticalPoint(prev->val, curr->val, next->val)) {
                if(firstCriticalPoint < 0) {
                    firstCriticalPoint = i;
                }
                if(currCriticalPoint > 0) {
                    minDist = min(minDist, i-currCriticalPoint);
                }
                currCriticalPoint = i;
            }
        }

        // Check if we have found at least two critical points
        if(minDist==numeric_limits<int>::max()) {
            return vector<int>({-1, -1});
        }
        return vector<int>({minDist, currCriticalPoint - firstCriticalPoint});
    }
};
