iclass Solution {
public:
    // Time: O(n²)
    // Space: O(n²)
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        vector<vector<int>> adj(n, vector<int>());
        // Building the graph
        for(int i=0; i<n; ++i) {
            // Left side
            for(int j=i-1; j>= max(i-d, 0) && arr[j] < arr[i]; --j) {
                adj[i].push_back(j);
            }

            // Right side
            for(int j=i+1; j<min(i+d+1, n) && arr[i] > arr[j]; ++j) {
                adj[i].push_back(j);
            }
        }
        // Computing depths on the DAG
        vector<int> depth(n);
        auto DFS = [&adj, &depth](this auto&& DFS, int node) -> void {
            int maxDepth = 0;
            for(int neigh : adj[node]) {
                if(!depth[neigh]) DFS(neigh);
                maxDepth = max(maxDepth, depth[neigh]);
            }
            depth[node] = 1 + maxDepth;
        };
        int ans = 0;
        for(int i=0; i<n; ++i) {
            if(!depth[i]) DFS(i);
            ans = max(ans, depth[i]); 
        }
        return ans;
    }
};
