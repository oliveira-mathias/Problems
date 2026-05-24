struct Node {
  int i, j, l;
};

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        vector<vector<vector<int>>> dist(m, vector<vector<int>>(n, vector<int>(k+1, -1)));

        if(grid[m-1][n-1] && k==0) return -1;


        queue<Node> q;
        Node start = {0,0,grid[0][0]};
        q.push(start);
        dist[0][0][grid[0][0]] = 0;
        
        while(!q.empty()) {
            Node node = q.front();
            q.pop();

            int i = node.i;
            int j = node.j;
            int l = node.l;

            if(i==m-1 && j==n-1 && dist[m-1][n-1][l]>=0) {
            return dist[m-1][n-1][l];
            }

            // Visiting neighbors
            if(i-1>=0) {
            int obstaclesInPath = l + grid[i-1][j];
            if(obstaclesInPath <= k && dist[i-1][j][obstaclesInPath]<0) {
                dist[i-1][j][obstaclesInPath] = dist[i][j][l] + 1;
                q.push({i-1, j, obstaclesInPath});
            }
            }
            if(i+1<m) {
            int obstaclesInPath = l + grid[i+1][j];
            if(obstaclesInPath <= k && dist[i+1][j][obstaclesInPath]<0) {
                dist[i+1][j][obstaclesInPath] = dist[i][j][l] + 1;
                q.push({i+1, j, obstaclesInPath});
            }
            }
            if(j-1>=0) {
            int obstaclesInPath = l + grid[i][j-1];
            if(obstaclesInPath <= k && dist[i][j-1][obstaclesInPath]<0) {
                dist[i][j-1][obstaclesInPath] = dist[i][j][l] + 1;
                q.push({i, j-1, obstaclesInPath});
            }
            }
            if(j+1<n) {
            int obstaclesInPath = l + grid[i][j+1];
            if(obstaclesInPath <= k && dist[i][j+1][obstaclesInPath]<0) {
                dist[i][j+1][obstaclesInPath] = dist[i][j][l] + 1;
                q.push({i, j+1, obstaclesInPath});
            }
            }
        }

        return -1;
      
    }
};
