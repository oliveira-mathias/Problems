class Solution {
public:
    // Time: O(m*n*(m+n))
    // Space: O(n*(m+n))
    bool hasValidPath(const vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        // Early exit, the path must have an even number of tiles
        if((m + n - 1)%2) return false;
        if(grid[0][0]==')' || grid[m-1][n-1]=='(') return false;

        // DP[i][j][k] = 1 <-> exists a path starting from (i, j) that has balance -k
        const int maxDelta = (m + n)/2;
        vector<vector<bool>> DP(n+1, vector<bool>(maxDelta+ 1, false));

        // Recursive case
        for(int i=m-1; i>=0; --i) {
            for(int j=n-1; j>=0; --j) {
                // Base case
                if(i==m-1 && j==n-1) {
                    DP[j][1] = true;
                }
                else if(grid[i][j]=='(') {
                    for(int k=0; k<maxDelta; ++k) {
                        // We use the own value here so that we don't overwrite the base case
                        DP[j][k] = (DP[j][k+1] || DP[j+1][k+1]);
                    }
                    DP[j][maxDelta] = false;
                }
                else {
                    for(int k=maxDelta; k>0; --k) {
                        DP[j][k] = (DP[j][k-1] || DP[j+1][k-1]);
                    }
                    DP[j][0] = false;
                }

            }
        }

        return DP[0][0];
    }
};
