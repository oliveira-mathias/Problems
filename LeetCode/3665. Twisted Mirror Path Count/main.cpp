class Solution {
public:
    // Time: O(m*n)
    // Space: O(n)
    int uniquePaths(const vector<vector<int>>& grid) {
        constexpr int MOD = 1000000007;
        int m = grid.size();
        int n = grid[0].size();

        // DP[i, j, D], where D \in {Up, Left}
        // DP[i, j, D] = number of unique paths from (i, j) to (m-1, n-1)
        // given that I entered cell (i, j) from side D
        vector<int> UDP(n+1);
        vector<int> LDP(n+1);

        for(int i=m-1; i>=0; --i) {
            for(int j=n-1; j>=0; --j) {
                // Base case
                if(i==m-1 && j==n-1) {
                    UDP[j] = 1;
                    LDP[j] = 1;
                    continue;
                }

                // Recursive case
                if(grid[i][j]) {
                    int LAns = UDP[j];
                    int UAns = LDP[j+1];

                    LDP[j] = LAns;
                    UDP[j] = UAns;
                }
                else {
                    int ans = (UDP[j] + LDP[j+1])%MOD;
                    UDP[j] = ans;
                    LDP[j] = ans;
                }
            }
        }

        return UDP[0];
    }
};
