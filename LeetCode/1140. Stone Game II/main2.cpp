class Solution {
public:
    // Time: O(n³)
    // Space: O(n²)
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        int maxM = n/2 + (n%2);

        int totalStones = 0;
        vector<vector<int>> DP(n+1,vector<int>(maxM+1));
        for(int i=n-1; i>=0; --i) {
            totalStones += piles[i];
            for(int M=maxM; M>0; --M) {
                int ans = -1000000;
                int currSum = 0;
                for(int k=0; k<2*M && i+k<n; ++k) {
                    currSum += piles[i+k];
                    ans = max(ans, currSum - DP[i+k+1][min(maxM, max(M, k+1))]);
                }
                DP[i][M] = ans;
            }
        }

        // Alice - Bob = DP[0][1]
        // Alice + Bob = totalStones
        return (DP[0][1] + totalStones)/2;
    }
};
