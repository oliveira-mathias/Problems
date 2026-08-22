class Solution {
public:
    // Time: O(n³)
    // Space: O(n²)
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        int maxM = n/2 + (n%2);

        vector<vector<int>> DP(n+1,vector<int>(maxM+1));

        // Base case
        fill(DP[n].begin(), DP[n].end(), 0);

        for(int i=n-1; i>=0; --i) {
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

        // Computing Alice score
        int score = 0;
        bool aliceTurn = true;
        for(int i=0, M=1; i<n;) {
            int ans = DP[i][M];
            int currSum = 0;
            for(int k=0; k<2*M && i+k<n; ++k) {
                currSum += piles[i+k];
                if(ans == currSum - DP[i+k+1][min(maxM, max(M, k+1))]) {
                    i = i+k+1;
                    M = min(maxM, max(M, k+1));
                    if(aliceTurn) {
                        score += currSum;
                    }
                    aliceTurn = !aliceTurn;
                    break;
                }
            }
        }

        return score;
    }
};
