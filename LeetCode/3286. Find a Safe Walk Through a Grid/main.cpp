class Solution {
public:
    // Time: O(nm log(nm))
    // Space: O(nm)
    bool findSafeWalk(const vector<vector<int>>& grid, int health) {
        int n = grid.size();
        int m = grid[0].size();

        // Subtract 1 to avoid overflows
        vector<vector<int>> dist(n, vector<int>(m, numeric_limits<int>::max() -1));
        vector<pair<int, int>> offsets = {{1,0}, {0,1}, {-1, 0}, {0, -1}};

        // We use Dijkstra's algorithm
        priority_queue<
            pair<int,pair<int, int>>,
            vector<pair<int,pair<int, int>>>,
            greater<pair<int,pair<int, int>>>
            > q;

        dist[0][0] = grid[0][0];
        q.push({dist[0][0], {0,0}});

        while(!q.empty()) {
            auto [nodeDist, node] = q.top();
            q.pop();

            auto [nodeX, nodeY] = node;

            // Checking if this node have already been visited
            if(nodeDist > dist[nodeX][nodeY]) continue;

            // We found the target
            if(nodeX==n-1 && nodeY==m-1) return health > nodeDist;

            // We visit the neightbors
            for(auto offset : offsets) {
                int neighX = node.first + offset.first;
                int neighY = node.second + offset.second;

                if(neighX >=0 && neighX < n && neighY >= 0 && neighY < m 
                    && nodeDist + grid[neighX][neighY] < dist[neighX][neighY])
                {
                    dist[neighX][neighY] = nodeDist + grid[neighX][neighY];
                    q.push({dist[neighX][neighY], {neighX, neighY}});    
                }
            }          

        }

        // We should never reach here
        return false;
    }
};
