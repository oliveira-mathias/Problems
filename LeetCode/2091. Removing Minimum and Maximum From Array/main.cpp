class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minimumDeletions(const vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;
        for(int i=0; i<nums.size(); ++i) {
            int num = nums[i];
            if(num > nums[maxIndex]) {
                maxIndex = i;
            }
            if(num < nums[minIndex]) {
                minIndex = i;
            }
        }
        
        int left = min(minIndex, maxIndex);
        int right  = max(minIndex, maxIndex);
        int toRemove = numeric_limits<int>::max();
        // Option 1: Remove prefix and suffix
        toRemove = min(toRemove, left + 1 + n - right);
        // Option 2: Remove only the prefix
        toRemove = min(toRemove, right + 1);
        // Option 3: Remove only the suffix
        toRemove = min(toRemove, n - left);
        return toRemove;
    }
};
