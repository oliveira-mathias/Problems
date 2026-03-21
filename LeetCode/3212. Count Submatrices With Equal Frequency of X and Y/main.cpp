class Solution {
public:
    // Time: O(mn)
    // Space: O(n)
    int numberOfSubmatrices(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid.back().size();

        vector<int> colCountX(n, 0);
        vector<int> colCountY(n, 0);

        // Counting submatrices
        // We check every possible lower corner
        int subMatrices = 0;
        for(int i=0; i<m; i++) {
            int rowPrefixXSum = 0;
            int rowPrefixYSum = 0;
            for(int j=0; j<n; ++j) {
                // Updating col count
                if(grid[i][j] == 'X') {
                    colCountX[j]++;
                }
                else if(grid[i][j] == 'Y') {
                    colCountY[j]++;
                }

                rowPrefixXSum += colCountX[j];
                rowPrefixYSum += colCountY[j];

                if(rowPrefixXSum && rowPrefixXSum==rowPrefixYSum) {
                    subMatrices++;
                }
            }
        }

        return subMatrices;
    }
};
