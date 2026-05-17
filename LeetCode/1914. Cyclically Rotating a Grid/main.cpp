class Solution {
public:
    // Time: O(m*n)
    // Space(O(m + n))
    vector<vector<int>> rotateGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<int> layer;
        layer.reserve(2*m + 2*n -4);

        auto layerNextPos = [](pair<int, int>& pos, pair<int, int>& topLeft, pair<int, int>& bottomRight) -> pair<int, int> {
            auto [i, j] = pos;
            auto [xTopLeft, yTopLeft] = topLeft;
            auto [xBottomRight, yBottomRight] = bottomRight;

            if(j == yTopLeft) {
                if(i == xBottomRight) {
                    return {xBottomRight, yTopLeft+1};
                }
                return {i+1, j};
            }
            if(i==xBottomRight) {
                if(j==yBottomRight) {
                    return {xBottomRight-1, yBottomRight};
                }
                return {i, j+1};
            }
            if(j==yBottomRight) {
                if(i==xTopLeft && yBottomRight==yTopLeft+1) {
                    return {-1, -1};
                }
                if(i==xTopLeft) {
                    return {xTopLeft, yBottomRight-1};
                }
                return {i-1, j};
            }
            if(i==xTopLeft) {
                if(j-1==yTopLeft) {
                    return {-1, -1};
                }
                return {i, j-1};
            }

            return {-1, -1};
        };

        const pair<int, int> sentinel = {-1, -1};
        int minDimension = min(m, n);
        for(int corner=0; corner<minDimension/2; ++corner) {
            pair<int, int> topLeft = {corner, corner};
            pair<int, int> bottomRight = {m-1-corner, n-1-corner};

            // Collect the layer elements
            layer.clear();
            for(pair<int, int> pos=topLeft; pos!=sentinel; pos=layerNextPos(pos, topLeft, bottomRight)) {
                const auto[i, j] = pos;
                layer.push_back(grid[i][j]);
            }

            // Removing rotation redundancies
            int offset = k % layer.size();
            if(offset == 0) continue;

            // Rotating the layer
            int currIndice = layer.size()-offset;
            for(pair<int, int> pos=topLeft; pos!=sentinel; pos=layerNextPos(pos, topLeft, bottomRight)) {
                const auto[i, j] = pos;
                if(currIndice==layer.size()) currIndice = 0;
                grid[i][j] = layer[currIndice];
                currIndice++;
            }
        }

        return grid;
    }
};
