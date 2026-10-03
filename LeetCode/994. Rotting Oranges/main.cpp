class Solution {
public:
    // Time: O(m*n)
    // Space: O(m*n)
    int orangesRotting(vector<vector<int>>& grid) {
        constexpr int EMPTY = 0;
        constexpr int FRESH = 1;
        constexpr int ROTTEN = 2;
        
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<int>> dist(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        int toRotten = 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(grid[i][j]==ROTTEN) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
                else if(grid[i][j]==FRESH) {
                    toRotten++;
                }
            }
        }

        constexpr int NUM_DIRS = 4;
        const int dirs[NUM_DIRS][2] = {
            {1,0},
            {-1,0},
            {0,1},
            {0,-1}
        };
        int maxDist = 0;
        while(!q.empty()) {
            const auto [x, y] = q.front();
            q.pop();

            // Visiting neighbors
            for(int i=0; i<NUM_DIRS; ++i) {
                int neighX = x + dirs[i][0];
                int neighY = y + dirs[i][1];

                if(neighX>=0 && neighX<m
                    && neighY>=0 && neighY<n
                    && grid[neighX][neighY]==FRESH
                    && dist[neighX][neighY] < 0)
                {
                    dist[neighX][neighY] = dist[x][y] + 1;
                    maxDist = max(maxDist, dist[neighX][neighY]);
                    toRotten--;
                    q.push({neighX, neighY});
                }
            }
        }
        if(toRotten > 0) return -1;
        else return maxDist;
    }
};
