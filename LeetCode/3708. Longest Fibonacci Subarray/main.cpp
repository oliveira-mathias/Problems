class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int longestSubarray(vector<int>& nums) {
        int maxSubarraySize = 2;
        int startIndex = 0;
        for(int nextIndex=2; nextIndex<=nums.size(); ++nextIndex) {
            long long nextSum = ((long long)nums[nextIndex-2]) + nums[nextIndex-1];
            
            // Here the sequence fails to extend
            if(nextIndex==nums.size() || nums[nextIndex] != nextSum) {
                maxSubarraySize = max(maxSubarraySize, nextIndex-startIndex);

                startIndex = nextIndex-1;
            }
        }
        return maxSubarraySize;
    }
};
