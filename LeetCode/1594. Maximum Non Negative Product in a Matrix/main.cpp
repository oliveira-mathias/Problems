class Solution {
public:
    static constexpr int MOD = 1000000007;
    // Time: O(nm)
    // Space: O(m)
    int maxProductPath(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<long long> DPP(m+1, -1); // For positive values
        vector<long long> DPN(m+1, -1); // For negative values


        for(int i=n-1; i>=0; --i) {
            for(int j=m-1; j>=0; --j) {
                if(i==n-1 && j==m-1) {
                    DPP[j] = (grid[i][j] >= 0) ? grid[i][j] : -1;
                    DPN[j] = (grid[i][j] <= 0) ? -grid[i][j] : -1; 
                    continue;
                }

                long long newDPP = -1;
                long long newDPN = -1;

                long long pathP = DPP[j];
                pathP = max(pathP, DPP[j+1]);

                long long pathN = DPN[j];
                pathN = max(pathN, DPN[j+1]);

                if(grid[i][j] > 0) {
                    if(pathP >= 0) {
                        newDPP = grid[i][j] * pathP;
                    }

                    if(pathN >= 0) {
                        newDPN = grid[i][j] * pathN;
                    }
                }
                else if(grid[i][j] < 0) {
                    long long absVal = -grid[i][j];
                    if(pathP >= 0) {
                        newDPN = absVal * pathP;
                    }

                    if(pathN >= 0) {
                        newDPP = absVal * pathN;
                    }
                }
                else {
                    newDPP = 0;
                    newDPN = 0;
                }

                DPP[j] = newDPP;
                DPN[j] = newDPN;
            }
        }

        return DPP[0] % MOD;
    }
};
