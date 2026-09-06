class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int firstStableIndex(const vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> suffixMin(n);

        suffixMin[n-1] = nums[n-1];
        for(int i=n-2; i>=0; --i) {
            suffixMin[i] = min(nums[i], suffixMin[i+1]);
        }

        int prefixMax = numeric_limits<int>::min();
        for(int i=0; i<n; ++i) {
            prefixMax = max(prefixMax, nums[i]);
            int instability = prefixMax - suffixMin[i];
            if(instability <= k) {
                return i;
            }
        }

        return -1;
    }
};
