class Solution {
public:
    // Time: O(m*n)
    // SPace: O(m*n)
    int closedIsland(const vector<vector<int>>& grid) {
        constexpr int NUM_NEIGHBORS = 4;
        int directions[NUM_NEIGHBORS][2] = {
            {1,0},{-1,0},{0,1},{0,-1}
        };

        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited (m, vector<bool>(n));
        const auto DFS = [&grid, &visited, &directions, m, n](this auto&& DFS, int x, int y) -> bool {
            // Base case
            if(visited[x][y]) return true;

            // Recursive case
            visited[x][y] = true;
            if(grid[x][y] == 1) return true;

            // Here we proceed with the flod fill
            bool valid = true;
            for(int i=0; i<NUM_NEIGHBORS; ++i) {
                int xNeigh = x + directions[i][0];
                int yNeigh = y + directions[i][1];

                // Checking if we have hited a boundary
                valid = valid && (xNeigh >= 0 && xNeigh < m && yNeigh >=0 && yNeigh < n);
                // Even if we conclude the component is invalid, we keep with the flod-fill
                // so that we mark the entire connected component 
                if(xNeigh >= 0 && xNeigh < m && yNeigh >=0 && yNeigh < n && !visited[xNeigh][yNeigh]) {
                    valid = DFS(xNeigh, yNeigh) && valid;
                }
            }
            return valid;
        };

        int islands = 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                if(!visited[i][j] && grid[i][j]==0) {
                    if(DFS(i, j)) {
                        islands++;
                    }
                }
            }
        }
        return islands;
    }
};
