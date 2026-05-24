class Solution {
public:
    // Time: O(m*n log(m*n))
    // Space: O(m*n)
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        const vector<pair<int, int>> directions = {
            {0, 1},
            {1, 0},
            {0, -1},
            {-1, 0}
        };

        vector<vector<int>> dist(m, vector<int>(n, numeric_limits<int>::max()));

        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;

        dist[0][0] = 0;
        q.push({0, {0, 0}});

        const auto isValidIndex = [m, n](int i, int j, int x, int y) -> bool {
            return (i + x >= 0) && (i + x < m) && (j + y >= 0) && (j + y < n); 
        };
        while(!q.empty()) {
            auto [nodeDist, node] = q.top();
            auto [i, j] = node;
            q.pop();

            // Skip node if it was already visited
            if(dist[i][j] < nodeDist) continue;
            // Mark node as visited

            if(i == m-1 && j == n-1) {
                return nodeDist;
            }

            // Visit neighbors
            for(const auto& dir : directions) {
                const auto [x, y] = dir;
                if(isValidIndex(i, j, x, y) && dist[i+x][j+y] > dist[i][j] + grid[i+x][j+y]) {
                    dist[i+x][j+y] = dist[i][j] + grid[i+x][j+y];
                    q.push({dist[i+x][j+y], {i+x, j+y}});
                }
            }
        }

        // We are sure to visit (m-1, n-1) but add this for safety
        return -1;
    }
};
