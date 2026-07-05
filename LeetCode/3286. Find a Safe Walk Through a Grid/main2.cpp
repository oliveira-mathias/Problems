class Solution {
public:
    // Time: O(mn)
    // Space: O(mn)
    bool findSafeWalk(const vector<vector<int>>& grid, int health) {
        int n = grid.size();
        int m = grid[0].size();

        // Subtract 1 to avoid overflows
        vector<vector<int>> dist(n, vector<int>(m, numeric_limits<int>::max() -1));
        vector<pair<int, int>> offsets = {{1,0}, {0,1}, {-1, 0}, {0, -1}};

        // We use 0-1 BFS algorithm
        std::deque<pair<int, int>> q;

        dist[0][0] = grid[0][0];
        q.push_front({0,0});

        while(!q.empty()) {
            auto [nodeX, nodeY] = q.front();
            q.pop_front();

            int nodeDist = dist[nodeX][nodeY];

            // We found the target
            if(nodeX==n-1 && nodeY==m-1) return health > nodeDist;

            // We visit the neightbors
            for(auto offset : offsets) {
                int neighX = nodeX + offset.first;
                int neighY = nodeY + offset.second;

                if(neighX >=0 && neighX < n && neighY >= 0 && neighY < m 
                    && nodeDist + grid[neighX][neighY] < dist[neighX][neighY])
                {
                    dist[neighX][neighY] = nodeDist + grid[neighX][neighY];
                    // 0-1 BFS
                    if(grid[neighX][neighY]) {
                        q.push_back({neighX, neighY});
                    }
                    else {
                        q.push_front({neighX, neighY});
                    }
                }
            }          

        }

        // We should never reach here
        return false;
    }
};
