class Solution {
public:
    // Time: O(amount*coins.size())
    // Space: O(amount)
    int coinChange(const vector<int>& coins, int amount) {
        // Base case: DP[0] = 0
        const int inf = numeric_limits<int>::max();
        vector<int> DP(amount+1);
        for(int i=1; i<=amount; ++i) {
            int ans = inf;
            for(int coin : coins) {
                if(i >= coin && DP[i-coin] < inf) {
                    ans = min(ans, 1 + DP[i-coin]);
                }
            }
            DP[i] = ans;
        }
        return (DP[amount]==inf) ? -1 : DP[amount];
    }
};
