class Solution {
public:
    int maximumJumps(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> DP(n);
        DP[n-1] = 1;

        for(int i=n-2; i>=0; --i) {
            int res = -1;

            for(int j=i+1; j<n; ++j) {
                if(nums[j]-nums[i] <= target && nums[j]-nums[i] >= -target) {
                    res = max(res, DP[j]);
                }
            }

            DP[i] = (res != -1) ? (res + 1) : -1;
        }

        // We are counting nodes, the answer is the number of edges
        return (DP[0] != -1) ? (DP[0] - 1) : -1;
    }
};
