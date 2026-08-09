class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    string stoneGameIII(const vector<int>& stoneValue) {
        int n = stoneValue.size();
        const auto generateResult = [](int score) -> string {
            if(score > 0) return "Alice";
            if(score < 0) return "Bob";
            return "Tie";
        };

        // Base case
        int DP[4] = {};
        DP[3] = stoneValue[n-1];
        if(n > 1) {
            DP[2] = max(stoneValue[n-2] - DP[3], stoneValue[n-2] + stoneValue[n-1]);
        }
        if(n > 2) {
            DP[1] = max({stoneValue[n-3] - DP[2], stoneValue[n-3] + stoneValue[n-2] - DP[3], stoneValue[n-3] + stoneValue[n-2] + stoneValue[n-1]});
        }
        if(n == 1) return generateResult(DP[3]);
        if(n == 2) return generateResult(DP[2]);
        if(n == 3) return generateResult(DP[1]);

        // Recursive solution
        for(int i=n-4; i>=0; --i) {
            int op1 = stoneValue[i] + stoneValue[i+1] + stoneValue[i+2] - DP[3];
            int op2 = stoneValue[i] + stoneValue[i+1] - DP[2];
            int op3 = stoneValue[i] - DP[1];

            // Update the DP array
            DP[0] = max(op1, max(op2, op3));
            DP[3] = DP[2];
            DP[2] = DP[1];
            DP[1] = DP[0];
        }
        return generateResult(DP[1]);
    }
};
