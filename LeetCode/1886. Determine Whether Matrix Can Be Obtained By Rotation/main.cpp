class Solution {
public:
    // Time: O(n²)
    // Space: O(1)
    bool findRotation(vector<vector<int>>& mat, vector<vector<int>>& target) {
        int n = mat.size();
        bool isEqual = true;
        bool isEqual90 = true;
        bool isEqual180 = true;
        bool isEqual270 = true;

        auto get90RotationIndex = [](int x, int y, int gridSide) -> pair<int, int> {
            return {gridSide -1 -y, x};
        };

        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if(mat[i][j] != target[i][j]) isEqual = false;

                auto [x90Rotated, y90Rotated] = get90RotationIndex(i, j, n);
                if(mat[i][j] != target[x90Rotated][y90Rotated]) isEqual90 = false;

                auto [x180Rotated, y180Rotated] = get90RotationIndex(x90Rotated, y90Rotated, n);
                if(mat[i][j] != target[x180Rotated][y180Rotated]) isEqual180 = false;

                auto [x270Rotated, y270Rotated] = get90RotationIndex(x180Rotated, y180Rotated, n);
                if(mat[i][j] != target[x270Rotated][y270Rotated]) isEqual270 = false;
            }
        }

        return isEqual || isEqual90 || isEqual180 || isEqual270;
    }
};
