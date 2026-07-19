struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        rank = vector<int>(n);
        parent = vector<int>(n);
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int node) {
        if(node == parent[node]) {
            return node;
        }

        return parent[node] = Find(parent[node]);
    }

    void Union(int n1, int n2) {
        int parent1 = Find(n1);
        int parent2 = Find(n2);

        if(rank[parent1] >= rank[parent2]) {
            parent[parent2] = parent1;
            if(rank[parent1] == rank[parent2]) {
                rank[parent1]++;
            }
        }
        else {
            parent[parent1] = parent2;
        }
    }
};

class Solution {
public:
    // Time: O(n + m*alpha(n))
    // Space: O(n)
    vector<bool> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        DSU dsu(n);

        for(int i=1; i<n; ++i) {
            if(nums[i] <= nums[i-1] + maxDiff) {
                dsu.Union(i-1, i);
            }
        }

        vector<bool> ans(queries.size());
        for(int i=0; i<queries.size(); ++i) {
            const auto& query = queries[i];
            int u = query[0];
            int v = query[1];

            ans[i] = (dsu.Find(u) == dsu.Find(v));       
        }
        return ans;
    }
};
