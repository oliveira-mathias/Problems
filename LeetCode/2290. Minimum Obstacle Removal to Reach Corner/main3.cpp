class Solution {
public:
    // Time: O(m*n)
    // Space: O(m*n)
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        auto isValidIndex = [m, n](int i, int j) -> bool {
            return (i >= 0) && (i < m) && (j >= 0) && (j < n);
        };

        const vector<pair<int, int>> directions = {
            {0,1}, {1,0}, {-1,0}, {0, -1}
        };

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        deque<pair<int, pair<int, int>>> q;
        q.push_back({0, {0,0}});
        visited[0][0]= true;
        while(!q.empty()) {
            auto [dist, node] = q.front();
            auto [i, j] = node;
            q.pop_front();

            if(i==m-1 && j==n-1) return dist;

            // Visit neighbors
            for(const auto& dir : directions) {
                auto [x, y] = dir;
                if(isValidIndex(i + x, j + y) && !visited[i+x][j+y]) {
                    visited[i+x][j+y] = true;
                    if(grid[i+x][j+y]) {
                        q.push_back({dist+1, {i+x, j+y}});
                    }
                    else {
                        q.push_front({dist, {i+x, j+y}});
                    }
                }
            }
        }

        // We are never going to reach here, but we add thisfor safetyness
        return -1;
    }
};
