class Solution {
public:
    // Time: O(mnk)
    // Space: O(nk)
    int maxPathScore(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> DP(n+1, vector<int>(k+1, -1));

        for(int i=m-1; i>=0; --i) {
            for(int j=n-1; j>=0; --j) {
                // Base case
                if(i==m-1 && j==n-1) {
                    int val = grid[i][j];
                    int cost = val ? 1 : 0;
                    if(cost <= k) {
                        DP[j][cost] = val;
                    }
                    continue;
                }

                // Recursive step
                int val = grid[i][j];
                int cost = val ? 1 : 0;
                for(int l=k; l>=0; --l) {
                    int delta = l-cost;
                    if(delta < 0) {
                        DP[j][l] = -1;
                    }
                    else {
                        int maxNeigh = max(DP[j][delta], DP[j+1][delta]);
                        if(maxNeigh != -1) {
                            DP[j][l] = val + maxNeigh;
                        }
                        else {
                            DP[j][l] = -1;
                        }
                    }
                }
            }
        }

        // Extracting the answer
        int val = -1;
        for(int i=k; i>=0; --i) {
            val = max(val, DP[0][i]);
        }
        return val;
    }
};
