class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minOperations(const vector<int>& nums) {
        int n = nums.size();
        int minMoves = numeric_limits<int>::max();
        // Searching for the index of the smallest elements
        int smallestIndex = 0;
        for(int i=1; i<n; ++i) {
            if(nums[i] == 0) {
                smallestIndex = i;
            }
        }
        // Case 1
        bool isInSortedOrder = true;
        int currIndex = smallestIndex;
        for(int i=0; i<n-1; ++i) {
            int nextIndex = currIndex==n-1 ? 0 : currIndex+1;
            if(nums[nextIndex] < nums[currIndex]) {
                isInSortedOrder = false;
                break;
            }
            currIndex = nextIndex;
        }
        if(isInSortedOrder) {
            // Option1: Rotate Left
            minMoves = min(minMoves, smallestIndex);
            // Option2: Rotate right
            minMoves = min(minMoves, n-smallestIndex+2);
        }
        // Case 2
        bool isInRevSortedOrder = true;
        currIndex = smallestIndex;
        for(int i=0; i<n-1; ++i) {
            int prevIndex = currIndex==0 ? n-1 : currIndex-1;
            if(nums[prevIndex] < nums[currIndex]) {
                isInRevSortedOrder = false;
                break;
            }
            currIndex = prevIndex;
        }
        if(isInRevSortedOrder) {
            // Option1: Rotate Left
            minMoves = min(minMoves, n-smallestIndex);
            // Option2: Rotate right
            minMoves = min(minMoves, smallestIndex+2);
        }
        return (!isInSortedOrder && !isInRevSortedOrder) ? -1 : minMoves;
    }
};
