class Solution {
public:
    // Time: O((n + m) log(maxCost))
    // Space: O(n + m)
    int findMaxPathScore(vector<vector<int>>& edges, vector<bool>& online, long long k) {
        int n = online.size();
        // Building the adjacency table
        vector<vector<pair<int, int>>> adj (n, vector<pair<int, int>>());
        int maxCost = numeric_limits<int>::min();
        int minCost = numeric_limits<int>::max();
        for(const auto& edge : edges) {
            int source = edge[0];
            int dest = edge[1];
            int cost = edge[2];
            
            maxCost = max(maxCost, cost);
            minCost = min(minCost, cost);
            adj[source].push_back({dest, cost});
        }

        // We binary search the answer
        vector<long long> dist(n);
        int l = minCost;
        int r = maxCost + 1;
        int ans = -1;
        // Quick exit case
        if(minCost > k) return -1;

        auto shortestDist = [&dist, &adj, &online, k](this auto&& shortestDist, int node, int threshold) -> long long {
            // Base case
            if(dist[node] >= 0) return dist[node];

            // Recursive step
            long long minDist = numeric_limits<long long>::max();
            for(auto [neigh, cost] : adj[node]) {
                if(online[neigh] && cost >= threshold) {
                    long long neighDist = shortestDist(neigh, threshold);
                    if(neighDist < numeric_limits<long long>::max()) {
                        minDist = min(minDist, neighDist + cost);
                    }
                }
            }
            return dist[node] = minDist;
        };
        while(l < r) {
            int m = l + (r-l)/2;
            // Reset the distances vector
            fill(dist.begin(), dist.end(), -1);
            dist.back() = 0;
            if(shortestDist(0, m) <= k) {
                ans = m;
                l = m+1;
            }
            else {
                r = m;
            }
        }
        return ans;
    }
};
