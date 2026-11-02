// gjh
class XORSegTree {
    int n;
    vector<unsigned> T;
    vector<unsigned> lazy;

    void buildRec(int node, int L, int R, const vector<unsigned>& v) {
        // Base case
        if(L == R) {
            T[node] = v[L];
            return;
        }

        // Recursive case
        int m = L + (R-L)/2;
        int leftNode = (node << 1);
        buildRec(leftNode, L, m, v);
        int rightNode = leftNode + 1;
        buildRec(rightNode, m+1, R, v);
        T[node] = T[leftNode] ^ T[rightNode];
    }

    void updateRec(int node, int L, int R, int i, int j, unsigned val) {
        int leftNode = (node << 1);
        int rightNode = leftNode + 1;
        // Base case
        // Case 1: No interception
        if(R < i || L > j) {
            return;
        }
        // Case 2: Fully contained
        if(L>=i && R<=j) {
            T[node] ^= val;
            if(L!=R) {
                lazy[leftNode] ^= val;
                lazy[rightNode] ^= val;
            }
            return;
        }

        // Recursive case
        int m = L + (R-L)/2;
        lazy[leftNode] ^= lazy[node];
        lazy[rightNode] ^= lazy[node];
        lazy[node] = 0;
        updateRec(leftNode, L, m, i, j, val);
        updateRec(rightNode, m+1, R, i, j, val);
        T[node] = T[leftNode]^T[rightNode];
    }

    unsigned queryRec(int node, int L, int R, int i, int j) {
        int leftNode = (node << 1);
        int rightNode = leftNode + 1;
        // Base case
        // Case 1: Don't intercept
        if(L > j || R < i) {
            return 0U;
        }
        // Case 2: Fully intercepts
        if(L >= i && R <= j) {
            T[node] ^= lazy[node];
            // Bubble down the lazy values
            if(L != R) {
                lazy[leftNode] ^= lazy[node];
                lazy[rightNode] ^= lazy[node];
            }
            lazy[node] = 0U;
            return T[node];
        }

        // Recursive case
        int m = L + (R-L)/2;
        lazy[leftNode] ^= lazy[node];
        lazy[rightNode] ^= lazy[node];
        lazy[node] = 0;
        return queryRec(leftNode, L, m, i, j) ^ queryRec(rightNode, m+1, R, i, j);
    }

    public:
    XORSegTree(int _n, const vector<unsigned>& v) {
        n = _n;
        T = vector<unsigned>(4*n+1);
        lazy = vector<unsigned>(4*n+1);
        buildRec(1, 0, n-1, v);
    }

    void update(int i, int j, unsigned val) {
        updateRec(1, 0, n-1, i, j, val);
    }

    unsigned query(int i, int j) {
        return queryRec(1, 0, n-1, i, j);
    }
};


class Solution {
public:
    // Time: O((n+m)log(n))
    // Space: O(n log(n) + m)
    vector<bool> palindromePath(int n, const vector<vector<int>>& edges, string s, const vector<string>& queries) {
        // Building the graph
        vector<vector<int>> adj(n, vector<int>());
        for(const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        // DFSing the tree
        vector<int> parent(n, 0);
        int currPos = 0;
        vector<pair<int, int>> subTreeRange(n);
        vector<unsigned> pathXOR(n);
        int logN = log2(n) + 1;
        vector<vector<int>> BL(n, vector<int>(logN+1));
        const auto DFS = [&adj, &parent, &currPos, &subTreeRange, &pathXOR, &s, logN, &BL](this auto&& DFS, int node) -> void {
            int startTime = currPos++;
            unsigned letter = 1U << (s[node]-'a');
            pathXOR[node] = pathXOR[parent[node]] ^ letter;

            // Computing the binary lifting
            BL[node][0] = parent[node];
            for(int i=1; i<=logN; ++i) {
                int jumpTarget = BL[node][i-1];
                BL[node][i] = BL[jumpTarget][i-1];
            }

            // Visiting children
            for(int child : adj[node]) {
                if(child != parent[node]) {
                    parent[child] = node;
                    DFS(child);
                }  
            }

            int endTime = currPos-1;
            subTreeRange[node] = {startTime, endTime};

        };
        DFS(0);

        // Computing the LCA
        const auto getLCA = [&subTreeRange, &BL, logN](int u, int v) -> int {
            auto [uStart, uEnd] = subTreeRange[u];
            auto [vStart, vEnd] = subTreeRange[v];

            // Check for containance
            if(uStart <= vStart && vStart <= uEnd) return u;
            if(vStart <= uStart && uStart <= vEnd) return v;

            // Doing the search
            for(int i=logN; i>=0; --i) {
                int jumpTarget = BL[u][i];
                auto[jumpStart, jumpEnd] = subTreeRange[jumpTarget];

                if(jumpStart > vStart || vStart > jumpEnd) {
                    u = jumpTarget;
                }
            }

            return BL[u][0];
        };

        vector<unsigned> permPathXOR(n);
        for(int i=0; i<n; ++i) {
            int permImage = subTreeRange[i].first;
            permPathXOR[permImage] = pathXOR[i];
        }

        // Creating the segment tree
        XORSegTree T(n, permPathXOR);

        // Processing the queries
        vector<bool> ans;
        ans.reserve(queries.size());
        for(const string& query : queries) {
            if(query[0] == 'u') {
                const int u = stoi(query.substr(7, query.size()-2));
                const char c = query[query.size()-1];
                unsigned queryMask = 1U << (s[u]-'a');
                queryMask ^= 1U << (c-'a');
                s[u] = c;
                auto [rangeStart, rangeEnd] = subTreeRange[u];
                T.update(rangeStart, rangeEnd, queryMask);
            }
            else {
                int splitSpot = 6;
                while(query[splitSpot] != ' ') splitSpot++;
                const int u = stoi(query.substr(6, splitSpot));
                const int v = stoi(query.substr(splitSpot+1, query.size()));
                const int uPos = subTreeRange[u].first;
                const int vPos = subTreeRange[v].first;
                const int lca = getLCA(u, v);
                unsigned queryAns = 1U << (s[lca]-'a');
                queryAns ^= T.query(uPos, uPos) ^ T.query(vPos, vPos);
                ans.push_back(__builtin_popcount(queryAns) <= 1);
            }
        }

        return ans;
    }
};

