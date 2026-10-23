class Solution {
public:
    // Time: O(n³ + n²*2^n)
    // Space: O(n² + n*2^n)
    int shortestPathLength(const vector<vector<int>>& graph) {
        int n = graph.size();
        int pow_n = (1U << n);
        // Simple case
        if(n==1) return 0;

        vector<vector<int>> adj(n, vector<int>(n, n));
        // Base case
        for(int i=0; i<n; ++i) adj[i][i] = 0;
        for(int i=0; i<n; ++i) {
            for(int j : graph[i]) {
                adj[i][j] = 1;
                adj[j][i] = 1;
            }
        }
        // Floyd-Warshal
        for(int k=0; k<n; ++k)
            for(int i=0; i<n; ++i)
                for(int j=0; j<n; ++j)
                    adj[i][j] = min(adj[i][j], adj[i][k] + adj[k][j]);

        // Shortest Path DP
        vector<vector<int>> DP(n, vector<int>(pow_n, numeric_limits<int>::max()));
        const auto solveDP = [&DP, &adj, n](this auto&& solveDP, int node, unsigned S) -> int {
            // Base case
            if(DP[node][S] < numeric_limits<int>::max()) {
                return DP[node][S];
            }
            if(S == (1U << node)) {
                return DP[node][S] = 0;
            }

            // Recursive case
            int ans = numeric_limits<int>::max();
            for(int i=0; i<n; ++i) {
                if(i==node || !(S & (1U << i))) continue;
                unsigned newS = S & (~(1U << node));
                ans = min(ans, adj[node][i] + solveDP(i, newS));
            }
            return DP[node][S] = ans;
        };
        int ans = numeric_limits<int>::max();
        unsigned fullSet = pow_n-1;
        for(int i=0; i<n; ++i) {
            ans = min(ans, solveDP(i, fullSet));
        }
        return ans;
    }
};
