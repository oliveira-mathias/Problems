class Solution {
public:
    // Time: O((n+k) log{nums[i]})
    // Space: O(1)
    int maxSum(const vector<int>& nums, int k) {
        constexpr int MASK_SIZE = 32;
        vector<int> bits(MASK_SIZE);
        for(int num : nums) {
            for(unsigned mask = 1U, currPow=0; mask != 0; mask <<= 1, currPow++) {
                if(num & mask) {
                    bits[currPow]++;
                }
            }
        }

        constexpr int MOD = 1000000007;
        int ans = 0;
        for(int i=0; i<k; ++i) {
            // Generating the k numbers
            unsigned long long num = 0;
            for(unsigned mask = 1U, currPow=0; mask!=0; mask <<=1, currPow++) {
                if(bits[currPow]) {
                    num |= mask;
                    bits[currPow]--;
                }
            }
            num = num*num;
            ans = (ans + num) % MOD;
        }
        return ans;
    }
};
