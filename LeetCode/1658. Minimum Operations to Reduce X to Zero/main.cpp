class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int minOperations(vector<int>& nums, int x) {
        int n = nums.size();
        unordered_map<int, int> prefixSum;
        // We can choose an empty prefix
        prefixSum[0] = -1;
        for(int i=0, currSum = 0; i<n; ++i) {
            currSum += nums[i];
            prefixSum[currSum] = i;
        }

        int minNums = n+1;
        auto it = prefixSum.find(x);
        // We can have an empty suffix
        if(it != prefixSum.end()) {
            minNums = it->second + 1;
        }
        for(int i=n-1, suffixSum=0; i>=0; --i) {
            suffixSum += nums[i];

            // Checking whether any solution is still feasible
            if(suffixSum > x) break;

            auto it = prefixSum.find(x - suffixSum);
            if(it != prefixSum.end()) {
                int prefixIdx = it->second;
                if(prefixIdx < i) {
                    minNums = min(minNums, prefixIdx + 1 + n - i);
                }
            }
        }
        return (minNums>nums.size()) ? -1 : minNums;
    }
};
