class Solution {
public:
    // Time: O(n log(n))
    // Space: O(n)
    long long maxAlternatingSum(vector<int> nums) {
        sort(nums.begin(), nums.end(),
        [](int a, int b) -> bool
        {
            return abs(a) < abs(b);
        });

        long long ans = 0;
        for(int i=0; i<nums.size(); ++i) {
            long long num = nums[i];
            long long term = (i < nums.size()/2) ? -num*num : num*num;
            ans += term;
        }
        return ans;
    }
};
