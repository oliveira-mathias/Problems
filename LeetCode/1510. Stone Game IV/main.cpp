class Solution {
public:
    // Time: O(n sqrt(n))
    // Space: O(n)
    bool winnerSquareGame(int n) {
        vector<bool> DP(n+1);
        for(int i=1; i<=n; ++i) {
            bool canWin = false;
            
            for(int k=1; k*k<=i; ++k) {
                if(!DP[i-k*k]) {
                    canWin = true;
                    break;
                }
            }
            DP[i] = canWin;
        }
        return DP[n];
    }
};
