class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int maxSubArray(const vector<int>& nums) {
        int currMaxSubarray = nums[0];
        int ans = nums[0];
        for(int i=1; i<nums.size(); ++i) {
            const int num = nums[i];
            // Choosing DP transition
            currMaxSubarray = max(currMaxSubarray + num, num);
            ans = max(ans, currMaxSubarray);
        }
        return ans;
    }
};
