class Solution {
public:
    // Time: O(n*d)
    // Space: O(n)
    int maxJumps(vector<int>& arr, int d) {
        int n = arr.size();
        // Computing depths on the DAG
        vector<int> depth(n);
        auto DFS = [&arr, &depth, d, n](this auto&& DFS, int node) -> void {
            int maxDepth = 0;
            // Left side
            for(int j=node-1; j>= max(node-d, 0) && arr[j] < arr[node]; --j) {
                if(!depth[j]) DFS(j);
                maxDepth = max(maxDepth, depth[j]);
            }

            // Right side
            for(int j=node+1; j<min(node+d+1, n) && arr[node] > arr[j]; ++j) {
                if(!depth[j]) DFS(j);
                maxDepth = max(maxDepth, depth[j]);
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
