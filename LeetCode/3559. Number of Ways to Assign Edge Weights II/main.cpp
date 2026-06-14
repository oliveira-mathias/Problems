class RMQ {
    int n;
    int sqrtN;
    vector<int> elems;
    vector<int> buckets; 

    public:
    RMQ(const vector<int>& euler, const vector<int>& heights) {
        n = euler.size();
        sqrtN = ceil(sqrt(n));

        elems.reserve(n);
        buckets.reserve(sqrtN);

        for(int i=0; i<euler.size(); i += sqrtN) {
            int minBucketHeight = numeric_limits<int>::max();
            for(int j=0; j<sqrtN && (i + j) < euler.size(); ++j) {
                int elem = heights[euler[i + j]];
                elems.push_back(elem);
                minBucketHeight = min(minBucketHeight, elem);
            }
            buckets.push_back(minBucketHeight);
        }
    }

    int query(int l, int r) {
        int firstBucket = (l/sqrtN) + 1;
        int lastBucket = r/sqrtN;
        int minElem = numeric_limits<int>::max();

        for(int i=l; i<=min(firstBucket*sqrtN, r); ++i) {
            minElem = min(minElem, elems[i]);
        }
        for(int i=firstBucket; i<lastBucket; ++i) {
            minElem = min(minElem, buckets[i]);
        }
        for(int i=max(l, lastBucket*sqrtN); i<=r; ++i) {
            minElem = min(minElem, elems[i]);
        }
        return minElem;
    }
};

class Solution {
public:
    // Time: O(n sqrt(n))
    // Space: O(n)
    vector<int> assignEdgeWeights(vector<vector<int>>& edges, vector<vector<int>>& queries) {
        // Building the graph
        int n = edges.size() + 1;
        vector<vector<int>> adj(n, vector<int>());
        for(const vector<int>& edge : edges) {
            int u = edge[0] - 1;
            int v = edge[1] - 1;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // LCA
        vector<int> eulerTour;
        eulerTour.reserve(2*n);
        vector<int> heights(n, -1);
        vector<int> firstOcc(n, -1);
        auto DFS = [&eulerTour, &heights, &firstOcc, &adj](this auto&& DFS, int node, int parent) -> void {
            heights[node] = heights[parent] + 1;
            firstOcc[node] = eulerTour.size();

            eulerTour.push_back(node);
            for(int neigh : adj[node]) {
                if(neigh != parent) {
                    DFS(neigh, node);
                    eulerTour.push_back(node);
                }
            }
        };
        // Assume root is node zero
        heights[0] = -1;
        DFS(0, 0);

        // RMQ for the height of the LCA
        RMQ rmq(eulerTour, heights);

        // DP
        constexpr int MOD = 1000000007;
        vector<int> oddPossibilities(n+1);
        oddPossibilities[1] = 1;
        for(int i=2; i<n+1; ++i) {
            oddPossibilities[i] = (2*oddPossibilities[i-1]) % MOD;
        }

        // Answer the queries
        vector<int> ans;
        ans.reserve(queries.size());
        for(const vector<int>& query : queries) {
            int u = query[0] - 1;
            int v = query[1] - 1;

            int start = firstOcc[u];
            int end = firstOcc[v];
            if(start > end) swap(start, end);

            // Height of the LCA
            int heightLCA = rmq.query(start, end);
            int pathSize = heights[u] + heights[v] -2*heightLCA;

            ans.push_back(oddPossibilities[pathSize]);
        }

        return ans;
    }
};
