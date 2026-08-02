class Solution {
public:
    // Time: O(n²)
    // Space: O(n²)
    bool predictTheWinner(const vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> DP(n, vector<int>(n));
        int parity  = n%2;
        for(int i=0; i<n; ++i) {
            DP[i][i] = (parity) ? nums[i] : -nums[i];
        }
        for(int len=1; len<n; ++len) {
            parity = 1-parity;
            for(int i=0, j=i+len; j<n; ++i, ++j){
                int op1 = DP[i+1][j];
                int op2 = DP[i][j-1];
                if(parity) {
                    DP[i][j] = max(nums[i] + op1, op2 + nums[j]);
                }
                else {
                    DP[i][j] = min(-nums[i] + op1, op2 - nums[j]);
                }
            }
        }
        return (DP[0][n-1] >= 0);
    }
};
