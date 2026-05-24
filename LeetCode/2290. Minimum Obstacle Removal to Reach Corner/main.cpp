class Solution {
public:
    // Time: O(m*n log(m*n))
    // Space: O(m*n)
    int minimumObstacles(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, numeric_limits<int>::min()));
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        priority_queue<pair<int, pair<int, int>>> q;

        dist[0][0] = 0;
        q.push({0, {0, 0}});

        while(!q.empty()) {
            auto [nodeNegDist, node] = q.top();
            auto [i, j] = node;
            q.pop();

            // Skip node if it was already visited
            if(visited[i][j]) continue;
            // Mark node as visited
            visited[i][j] = true;

            if(i == m-1 && j == n-1) {
                return -nodeNegDist;
            }

            // Visit neighbors
            if(i-1 >= 0 && !visited[i-1][j] && dist[i-1][j] < dist[i][j] - grid[i-1][j]) {
                dist[i-1][j] = dist[i][j] - grid[i-1][j];
                q.push({dist[i-1][j], {i-1, j}});
            }
            if(i+1 < m && !visited[i+1][j] && dist[i+1][j] < dist[i][j] - grid[i+1][j]) {
                dist[i+1][j] = dist[i][j] - grid[i+1][j];
                q.push({dist[i+1][j], {i+1, j}});
            }
            if(j-1 >= 0 && !visited[i][j-1] && dist[i][j-1] < dist[i][j] - grid[i][j-1]) {
                dist[i][j-1] = dist[i][j] - grid[i][j-1];
                q.push({dist[i][j-1], {i, j-1}});
            }
            if(j+1 < n && !visited[i][j+1] && dist[i][j+1] < dist[i][j] - grid[i][j+1]) {
                dist[i][j+1] = dist[i][j] - grid[i][j+1];
                q.push({dist[i][j+1], {i, j+1}});
            }
        }

        // We are sure to visit (m-1, n-1) but add this for safety
        return -1;
    }
};
