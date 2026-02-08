class Solution {
public:
    // Time: O(n log(n))
    // Space: O(log(n))
    int minRemoval(vector<int>& nums, int k) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        int minRemovals = n;
        for(int left=0, right=0; right < n; left++) {
            long long upperLimit = ((long long)k)*nums[left];

            // Search for the first excluded element
            while(right < n && nums[right] <= upperLimit) {
                right++;
            } 

            minRemovals = min(minRemovals, left + (n-right));
        }

        return minRemovals;
    }
};

