class Solution {
public:
    // Time: O(n²)
    // Space: O(n)
    bool predictTheWinner(const vector<int>& nums) {
        int n = nums.size();

        vector<int> DP(n);
        int parity  = n%2;
        for(int i=0; i<n; ++i) {
            DP[i] = (parity) ? nums[i] : -nums[i];
        }
        for(int len=1; len<n; ++len) {
            parity = 1-parity;
            for(int i=0, j=i+len; j<n; ++i, ++j){
                int op1 = DP[i+1];
                int op2 = DP[i];
                if(parity) {
                    DP[i] = max(nums[i] + op1, op2 + nums[j]);
                }
                else {
                    DP[i] = min(-nums[i] + op1, op2 - nums[j]);
                }
            }
        }
        return (DP[0] >= 0);
    }
};
