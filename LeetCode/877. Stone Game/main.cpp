class Solution {
public:
    // Time: O(n²)
    // Space: O(n)
    bool stoneGame(const vector<int>& piles) {
        // DP[i, j] = greatest difference for a player stating on piles[i:j]
        // DP[i, j] -> DP[i+1, j] or DP[i, j-1]
        int n = piles.size();
        vector<int> DP(n);

        // Base case
        copy(piles.begin(), piles.end(), DP.begin());

        for(int len=2; len<piles.size(); ++len) {
            for(int i=0; i+len < piles.size(); ++i) {
                int j = i+len;
                int opt1 = DP[i]; // DP[i] = DP[i, j-1]
                int opt2 = DP[i+1]; // DP[i+1] = DP[i+1, j]
                DP[i] = max(piles[i] - opt2, piles[j] - opt1);
            }
        }

        return (DP[0] > 0);

    }
};
