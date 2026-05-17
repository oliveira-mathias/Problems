class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int maxRotateFunction(vector<int>& nums) {
        int n = nums.size();
        int currSum = 0;
        int totalSum = 0;

        // Compute first sum
        for(int i=0; i<n; ++i) {
            currSum += i*nums[i];
            totalSum += nums[i];
        }

        int maxSum = currSum;
        // Compute the rotated sums
        for(int i=1; i<n; ++i) {
            // Adjusting the weights
            currSum -= totalSum - nums[i-1];
            // Inserting the new element in the sum
            currSum += (n-1)*nums[i-1];

            maxSum = max(maxSum, currSum);
        }

        return maxSum;
    }
};
