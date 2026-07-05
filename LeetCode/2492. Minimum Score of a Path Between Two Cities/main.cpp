struct DSU {
    vector<int> parent;
    vector<int> rank;

    DSU(int n) {
        parent = vector<int>(n);
        rank = vector<int>(n, 0);

        for(int i=0; i<n; ++i) parent[i] = i;
    }

    int Find(int node) {
        if(node == parent[node]) {
            return node;
        }

        return parent[node] = Find(parent[node]);
    }

    void Union(int node1, int node2) {
        int parent1 = Find(node1);
        int parent2 = Find(node2);

        if(rank[parent1] >= rank[parent2]) {
            parent[parent2] = parent1;
            if(rank[parent1] == rank[parent2]) rank[parent1]++;
        }
        else {
            parent[parent1] = parent2;
        }
    }
};

class Solution {
public:
    // Time: O(E alpha(n))
    // Space: O(n)
    int minScore(int n, const vector<vector<int>>& roads) {
        DSU conn(n);

        for(const vector<int>& road : roads) {
            int node1 = road[0]-1;
            int node2 = road[1]-1;
            conn.Union(node1, node2);
        }

        int minEdge = numeric_limits<int>::max();
        for(const vector<int>& road : roads) {
            int node1 = road[0]-1;
            int node2 = road[1]-1;
            int dist = road[2];

            // If they are in the connected component of the node 0
            if(conn.Find(node1)==conn.Find(0)) {
                minEdge = min(minEdge, dist);
            }
        }

        return minEdge;
    }
};
