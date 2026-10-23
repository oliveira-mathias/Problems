class Solution {
public:
    // Time: O(n²* 2^n)
    // Space: O(n * 2^n)
    int shortestPathLength(const vector<vector<int>>& graph) {
        int n = graph.size();
        int pow_n = (1U << n);
        // Simple case
        if(n==1) return 0;

        vector<vector<int>> dist(n, vector<int>(pow_n, numeric_limits<int>::max()));
        queue<pair<int, unsigned>> q;
        // Adding sources
        for(int i=0; i<n; ++i) {
            q.push({i, 1U<<i});
            dist[i][1U<<i] = 0;
        }
        // Doing the search
        while(!q.empty()) {
            auto [node, S] = q.front();
            q.pop();

            for(int neigh : graph[node]) {
                unsigned neighS = S | (1U<<neigh);
                // We only process unvisited nodes
                if(dist[neigh][neighS] == numeric_limits<int>::max()) {
                    dist[neigh][neighS] = 1+dist[node][S];
                    // Checking if we reached the destination
                    if(neighS == pow_n-1) return dist[neigh][neighS];
                    q.push({neigh, neighS});
                }
            }
        }
        // We should never reach here
        return -1;
    }
};
