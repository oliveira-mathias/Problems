class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int minJumps(vector<int>& arr) {
        // Collect edges
        unordered_map<int, vector<int>> adj;
        for(int i=0; i<arr.size(); ++i) {
            adj[arr[i]].push_back(i);
        }

        // Run BFS
        queue<int> q;
        vector<int> dist(arr.size(), -1);
        q.push(0);
        dist[0] = 0;
        while(!q.empty()) {
            int node = q.front();
            q.pop();

            // We break out if we found the target
            if(node+1==arr.size()) break;

            // Visiting the neighbors
            if(node-1 >=0 && dist[node-1] < 0) {
                q.push(node-1);
                dist[node-1] = dist[node] + 1;
            }
            if(node+1 < arr.size() && dist[node+1] < 0) {
                q.push(node+1);
                dist[node+1] = dist[node] + 1;
            }
            for(int neigh : adj[arr[node]]) {
                if(dist[neigh] < 0) {
                    q.push(neigh);
                    dist[neigh] = dist[node] + 1;
                }
            }
            adj[arr[node]].clear();
        }
        return dist.back();
    }
};
