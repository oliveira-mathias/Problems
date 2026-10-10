class Solution {
public:
    // Time: O(mn)
    // Space: O(mn)
    int numIslands(const vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        const auto DFS = [&grid, &visited, m, n](this auto&& DFS, int x, int y) -> void {
            visited[x][y] = true;

            constexpr int NUM_NEIGHS = 4;
            int neighs[NUM_NEIGHS][2] = {{x-1, y}, {x+1, y}, {x, y-1}, {x, y+1}};
            for(int i=0; i<NUM_NEIGHS; ++i) {
                int xNeigh = neighs[i][0];
                int yNeigh = neighs[i][1];
                if(xNeigh >= 0 && xNeigh < m && yNeigh >= 0 && yNeigh < n && !visited[xNeigh][yNeigh] && grid[xNeigh][yNeigh]=='1')
                {
                    DFS(xNeigh, yNeigh);
                }
            }
        };
        int islands = 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(!visited[i][j] && grid[i][j]=='1') {
                    islands++;
                    DFS(i, j);
                }
            }
        }
        return islands;
    }
};
