class Solution {
    static constexpr int MOD = 1000000007;
public:
    // Time: O((n + Q) log(n))
    // Space: O(n log(n))
    vector<int> assignEdgeWeights(const vector<vector<int>>& edges, const vector<vector<int>>& queries) {
        int n = edges.size() + 1;

        // Building the graph
        vector<vector<int>> adj (n, vector<int>());
        for(const vector<int>& edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> heights(n);
        heights[0] = -1; // Initialize so recursion works properly
        vector<pair<int, int>> ranges(n);
        const int logN = ceil(log2(n));
        vector<vector<int>> up(n, vector<int>(logN + 1));
        int timestemp = 0;

        auto DFS = [&adj, &heights, &ranges, &up, &timestemp, logN](this auto&& DFS, int node, int parent) -> void {
            ranges[node].first = ++timestemp;
            heights[node] = heights[parent] + 1;

            // Filling the table
            up[node][0] = parent;
            for(int i=1; i<=logN; ++i) {
                int halfwayParent = up[node][i-1];
                up[node][i] = up[halfwayParent][i-1];
            }

            // Visiting childs
            for(int child : adj[node]) {
                if(child != parent) {
                    DFS(child, node);
                }
            }

            ranges[node].second = ++timestemp;
        };
        DFS(0, 0);

        // Computing distance DP
        vector<int> DP(n);
        DP[1] = 1;
        for(int i=2; i<n; ++i) {
            DP[i] = (2*DP[i-1])%MOD;
        }

        // Answering queries
        auto contains = [](const pair<int, int>& p1, const pair<int, int>& p2) -> bool {
            // Does p1 contains p2?
            return p1.first <= p2.first && p2.second <= p1.second;
        };
        auto LCA = [&up, &ranges, &contains, logN](int u, int v) -> int {
            if(contains(ranges[u], ranges[v])) return u;
            if(contains(ranges[v], ranges[u])) return v;

            for(int j=logN; j>=0; --j) {
                int uParent = up[u][j];
                if(!contains(ranges[uParent], ranges[v])) {
                    u = uParent;
                }
            }

            return up[u][0];
        };
        vector<int> ans;
        ans.reserve(queries.size());
        for(const vector<int>& query : queries) {
            int u = query[0]-1;
            int v = query[1]-1;

            int uLCAv = LCA(u, v);

            int pathLen = heights[u] + heights[v] - 2*heights[uLCAv];
            ans.push_back(DP[pathLen]);
        }
        return ans;
    }
};
