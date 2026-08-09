class Solution {
public:
    // Time: O(n + m)
    // Space: O(n + m)
    vector<int> remainingMethods(int n, int k, vector<vector<int>>& invocations) {
        vector<vector<int>> adj(n, vector<int>());
        for(const vector<int>& edge :  invocations) {
            int a = edge[0];
            int b = edge[1];
            adj[a].push_back(b);
        }

        vector<bool> visited(n);
        queue<int> q;
        q.push(k);
        visited[k] = true;
        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(int neigh : adj[node]) {
                if(!visited[neigh]) {
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }

        // Validating removal possibility
        for(const vector<int>& edge : invocations) {
            int a = edge[0];
            int b = edge[1];
            if(!visited[a] && visited[b]) {
                // Here we have an edge that makes impossible to remove the k projects
                vector<int> res(n);
                iota(res.begin(), res.end(), 0);
                return res;
            }
        }

        // Here we just need to remove the visited nodes
        vector<int> res;
        for(int i=0; i<n; ++i) {
            if(!visited[i]) {
                res.push_back(i);
            }
        }
        return res;
    }
};
