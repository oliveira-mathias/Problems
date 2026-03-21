class Solution {
public:
    // Time: O(k²)
    // Space: O(1)
    vector<vector<int>> reverseSubmatrix(vector<vector<int>>& grid, int x, int y, int k) {
        auto exchangeRows = [&grid](int xRow1, int xRow2, int yStart, int yEnd) -> void {
            for(int j=yStart; j<=yEnd; ++j) {
                swap(grid[xRow1][j], grid[xRow2][j]);
            }
        };

        for(int lowerRow=x, upperRow=x+k-1; lowerRow<upperRow; ++lowerRow, --upperRow) {
            exchangeRows(lowerRow, upperRow, y, y+k-1);
        }

        return grid;
    }
};
