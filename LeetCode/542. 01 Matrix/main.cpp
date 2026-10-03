class Solution {
public:
    // Time: O(m*n)
    // Space: O(m*n)
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size();
        int n = mat[0].size();

        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        // Collecting zeros
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(mat[i][j]==0) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }
        // BFS search
        constexpr int NUM_DIRS = 4;
        const int dirs[NUM_DIRS][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        while(!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            // Visiting neighbors
            for(int i=0; i<NUM_DIRS; ++i) {
                int neighX = x + dirs[i][0];
                int neighY = y + dirs[i][1];
                if(neighX>=0 && neighX<m && neighY>=0 && neighY<n 
                    && dist[neighX][neighY] < 0)
                {
                    dist[neighX][neighY] = dist[x][y] + 1;
                    q.push({neighX, neighY});
                }
            }
        }
        return dist;
    }
};
