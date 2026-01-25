class Solution {
public:
    // Time: O(n*m*min{n,m}²)
    // Space: O(min {n , m})
    int largestMagicSquare(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid.front().size();
        int maxSide = 1;
        vector<int> rowSum, colSum;

        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                rowSum.clear();
                colSum.clear();
                int diagSum = 0;
                for(int side=1; (i + side <= n) && (j + side <= m); ++side) {
                    // Updating rowSum and ColSum
                    for(int k=0; k<side-1; ++k) {
                        rowSum[k] += grid[i+k][j+side-1];
                        colSum[k] += grid[i+side-1][j+k];
                    }
                    // Computing new rowSum and new colSum
                    rowSum.push_back(0);
                    colSum.push_back(0);
                    for(int k=0; k<side; ++k) {
                        rowSum.back() += grid[i+side-1][j+k];
                        colSum.back() += grid[i+k][j+side-1];
                    }
                    // Updating the diagonal
                    diagSum += grid[i+side-1][j+side-1];
                    // Computing  anti diagonal sum
                    int antiDiagSum = 0;
                    for(int k=0; k<side; ++k) {
                        antiDiagSum += grid[i+k][j+side-1-k];
                    }
                    // Checking if the square is magic
                    auto isConstArray = [](vector<int>& v) {
                        for(int num : v) {
                            if(num != v[0])
                                return false;
                        }
                        return true;
                    };

                    if((diagSum == antiDiagSum) &&
                        (diagSum == rowSum.front()) &&
                        (diagSum == colSum.front()) &&
                        isConstArray(rowSum) &&
                        isConstArray(colSum)
                    ) {
                        maxSide = max(maxSide, side);
                    }
                }
            }
        }

        return maxSide;
    }
};
