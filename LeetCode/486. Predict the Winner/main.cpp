class Solution {
public:
    // Time: O(n²)
    // Space: O(n²)
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();

        vector<vector<int>> DP(n, vector<int>(n, numeric_limits<int>::min()));
        const auto computeDP = [&DP, &nums](this auto&& computeDP, int i, int j, bool isP1Turn) -> int {
            if(DP[i][j] != numeric_limits<int>::min()) {
                return DP[i][j];
            }

            // Base case
            if(j==i) {
                return DP[i][j] = (isP1Turn) ? nums[i] : -nums[i];
            }

            // Recursive step
            int op1 = computeDP(i+1, j, !isP1Turn);
            int op2 = computeDP(i, j-1, !isP1Turn);
            if(isP1Turn) {
                return DP[i][j] = max(nums[i] + op1, op2 + nums[j]);
            }
            else {
                return DP[i][j] = min(-nums[i] + op1, op2 - nums[j]);
            }
        };

        return (computeDP(0, n-1, true) >= 0);
    }
};
