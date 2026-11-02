static constexpr int ALPHA_SIZE = 26;

class SegTree {
    int n;
    vector<vector<int>> T;
    vector<int> activeIndex;

    void updateRec(int node, int L, int R, int pos, char c) {
        // Base case
        if(L==R) {
            int oldActivePos = activeIndex[pos];
            int newActivePos = c-'a';
            if(oldActivePos >= 0) {
                T[node][oldActivePos] = 0;
            }
            T[node][newActivePos] = 1;
            activeIndex[pos] = newActivePos;
            return;
        }

        // Recursive case
        // Fix the node
        int toSubPos = activeIndex[pos];
        int toAddPos = c-'a';
        if(toSubPos >= 0) {
            T[node][toSubPos]--;
        }
        T[node][toAddPos]++;
        // Move downward
        int m = L + (R-L)/2;
        if(pos <= m) {
            int leftNode = 2*node;
            updateRec(leftNode, L, m, pos, c);
        }
        else {
            int rightNode = 2*node + 1;
            updateRec(rightNode, m+1, R, pos, c);
        }
    }

    void queryRec(int node, int L, int R, int i, int j, vector<int>& ans) {
        // Base case
        // Case 1: Do not intersect
        if(i > R || j < L) {
            return;
        }
        // Case 2: Fully contained
        if(L >= i && R<= j) {
            for(int i=0; i<ALPHA_SIZE; ++i) {
                ans[i] += T[node][i];
            }
            return;
        }

        // Recursive case
        int m = L + (R-L)/2;
        int leftNode = 2*node;
        queryRec(leftNode, L, m, i, j, ans);
        int rightNode = leftNode + 1;
        queryRec(rightNode, m+1, R, i, j, ans);
    }

    void buildRec(int node, int L, int R, const string& s) {
        // Base case
        if(L == R) {
            int charIndex = s[L]-'a';
            T[node][charIndex] = 1;
            activeIndex[L] = charIndex;
            return;
        }

        // Recursive case
        int m = L + (R-L)/2;
        int leftNode = 2*node;
        buildRec(leftNode, L, m, s);
        int rightNode = leftNode + 1;
        buildRec(rightNode, m+1, R, s);
        for(int i=0; i<ALPHA_SIZE; ++i) T[node][i] = T[leftNode][i] + T[rightNode][i];
    }

    public:
    SegTree(int _n, const string& s) {
        n = _n;
        T = vector<vector<int>>(4*n+1, vector<int>(ALPHA_SIZE));
        activeIndex = vector<int>(n);
        buildRec(1, 0, n-1, s);
    }

    void update(int pos, char c) {
        updateRec(1, 0, n-1, pos, c);
    }

    void query(int i, int j, vector<int>& ans) {
        return queryRec(1, 0, n-1, i, j, ans);
    }

};

class Solution {
public:
    // Time: O(n + q log²(n))
    // Space: O(n + q)
    vector<bool> palindromePath(int n, const vector<vector<int>>& edges, const string& s, const vector<string>& queries) {
        // Building the graph
        vector<vector<int>> adj(n, vector<int>());
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        // Computing the HLD
        vector<int> heavyChild (n, -1);
        vector<int> parentNode (n, 0);
        vector<int> depth(n, 0);
        const auto DFS = [&adj, &heavyChild, &parentNode, &depth](this auto&& DFS, int node, int parent) -> int {
            parentNode[node] = parent;
            depth[node] = depth[parent] + 1;
            int componentSize = 1;

            int maxChildSize = -1;
            for(int child : adj[node]) {
                if(child == parent) continue;
                int childSize = DFS(child, node);
                componentSize += childSize;
                if(childSize > maxChildSize) {
                    maxChildSize = childSize;
                    heavyChild[node] = child;
                }
            }
            // -1 for parent, +1 for self node
            return componentSize;
        };
        DFS(0, 0);

        // Spliting the components
        vector<int> componentHead (n, 0);
        vector<int> order(n, 0);
        int currPos = 0;
        const auto splitComponents = [&parentNode, &heavyChild, &componentHead, &adj, &order, &currPos](this auto&& splitComponents, int node, int currentHead) -> void {
            componentHead[node] = currentHead;
            order[node] = currPos++;
            if(heavyChild[node] >= 0) {
                splitComponents(heavyChild[node], currentHead);
            }

            for(int child :  adj[node]) {
                if(child != parentNode[node] && child != heavyChild[node]) {
                    splitComponents(child, child);
                }
            }
        };
        splitComponents(0, 0);

        // Creating the segTree
        string sPerm(s.size(), ' ');
        for(int i=0; i<n; ++i) {
            sPerm[order[i]] = s[i];
        }
        SegTree T(n, sPerm);

        // HLD query function
        const auto HLDQuery = [&depth, &order, &componentHead, &parentNode, &T](int a, int b, vector<int>& ans) -> void {
            for(; componentHead[a] != componentHead[b]; b = parentNode[componentHead[b]]) {
                if(depth[componentHead[a]] > depth[componentHead[b]]) {
                    swap(a, b);
                }
                T.query(order[componentHead[b]], order[b], ans);
            }
            // Final heavy component
            if(depth[a] > depth[b]) swap(a, b);
            T.query(order[a], order[b], ans);
        };

        vector<bool> ans;
        ans.reserve(queries.size());
        vector<int> freq(ALPHA_SIZE);
        for(const string& query : queries) {
            if(query[0] == 'u') {
                // int target = stoi(query.substr(7, query.size() -2));
                int target = 0;
                for(int i=7; i<query.size()-2; ++i) {
                    int digit = query[i]-'0';
                    target = 10*target + digit;
                }
                char c = query[query.size()-1];
                T.update(order[target], c);
            }
            else {
                int splitSpot = 6;
                // int u = stoi(query.substr(6, splitSpot));
                int u=0;
                while(query[splitSpot] != ' ') {
                    int digit = query[splitSpot]-'0';
                    u = 10*u + digit;
                    splitSpot++;
                }
                // int v = stoi(query.substr(splitSpot+1, query.size()));
                int v = 0;
                for(int i=splitSpot+1; i<query.size(); ++i) {
                    int digit = query[i]-'0';
                    v = 10*v + digit;
                }
                fill(freq.begin(), freq.end(), 0);
                HLDQuery(u, v, freq);
                int oddCompCount = 0;
                for(int i=0; i<ALPHA_SIZE; ++i) {
                    if(freq[i]%2) {
                        oddCompCount++;
                    }
                }
                ans.push_back(oddCompCount <= 1);
            }
        }
        return ans;
    }
};
