class Solution {
public:
    // Time: O(n + m)
    // Space: O(n + m)
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj(n, vector<int>());
        for(const vector<int>& edge :  edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        vector<bool> visited (n, false);
        auto componentSize = [&adj, &visited](this auto&& componentSize, int node) -> pair<int, int> {
            visited[node] = true;
            int nodes = 1;
            int degrees = adj[node].size();
            for(int neigh : adj[node]) {
                if(!visited[neigh]) {
                    auto [neighNodes, neighDegrees] = componentSize(neigh);
                    nodes += neighNodes;
                    degrees += neighDegrees;
                }
            }
            return {nodes, degrees};
        };
        int completeComponents = 0;
        for(int i=0; i<n; ++i) {
            if(!visited[i]) {
                auto [nodeCount, degreeCount] = componentSize(i);
                int componentEdges = degreeCount/2;
                int maxComponentEdges = (nodeCount*(nodeCount-1))/2;
                if(componentEdges == maxComponentEdges) completeComponents++;
            }
        }
        return completeComponents;
    }
};
