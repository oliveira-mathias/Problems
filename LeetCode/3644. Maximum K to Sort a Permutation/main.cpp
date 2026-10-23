class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int sortPermutation(const vector<int>& nums) {
        unsigned ans = 0xffffffffU;
        for(unsigned i=0; i<nums.size(); ++i) {
            if(nums[i] != i) {
                ans = ans & i;
            }
        }
        return (ans == 0xffffffffU) ? 0 : ans;
    }
};
