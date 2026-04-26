class Solution {
public:
    // Time: O(n*m)
    // Space: O(n*m)
    bool containsCycle(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();

        vector<vector<bool>> visited(n, vector<bool>(m, false));
        const auto DFS = [&grid, &visited, n, m](this auto&& DFS, int parentX, int parentY, int x, int y) -> bool {
            if(visited[x][y]) return true;
            
            visited[x][y] = true;
            char currChar = grid[x][y];

            bool foundCycle = false;
            if(x > 0 && x-1 != parentX && grid[x-1][y]==currChar) {
                foundCycle = foundCycle || DFS(x, y, x-1, y);
            }
            if(y > 0 && y-1 != parentY && grid[x][y-1]==currChar) {
                foundCycle = foundCycle || DFS(x, y, x, y-1);
            }
            if(x < n-1 && x+1 != parentX && grid[x+1][y]==currChar) {
                foundCycle = foundCycle || DFS(x, y, x+1, y);
            }
            if(y < m-1 && y+1 != parentY && grid[x][y+1]==currChar) {
                foundCycle = foundCycle || DFS(x, y, x, y+1);
            }

            return foundCycle;
        };

        for(int x=0; x<n; ++x) {
            for(int y=0; y<m; ++y) {
                if(!visited[x][y]) {
                    if(DFS(x, y, x, y)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};
