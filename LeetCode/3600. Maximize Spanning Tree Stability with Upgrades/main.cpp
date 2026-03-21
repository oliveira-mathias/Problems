class DSU {
    vector<int> parent;
    vector<int> rank;

    public:
    DSU(int n) {
        parent.reserve(n);
        rank.resize(n);

        for(int i=0; i<n; i++) {
            parent.push_back(i);
        }

        fill(rank.begin(), rank.end(), 1);
    }

    // Path compression
    int Find(int idx) {
        if(idx == parent[idx]) return idx;

        return parent[idx] = Find(parent[idx]);
    }

    // Union by rank
    void Union(int idx1, int idx2) {
        int parent1 = Find(idx1);
        int parent2 = Find(idx2);

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
    // Time: O(m log(m))
    // Space: O(m + n)
    int maxStability(int n, vector<vector<int>>& edges, int k) {
        // We will sort the edges, by must and them by strength
        sort(edges.begin(), edges.end(), 
            [](const vector<int>& a, const vector<int>& b) {
                int mustA = a[3];
                int mustB = b[3];

                int strengthA = a[2];
                int strengthB = b[2];

                return (mustA > mustB) || (mustA == mustB && strengthA > strengthB);
            }
        );

        DSU components(n);
        vector<int> treeEdges;
        treeEdges.reserve(n-1);

        for(int i=0; i<edges.size(); ++i) {
            int uEdge = edges[i][0];
            int vEdge = edges[i][1];
            int mustEdge = edges[i][3];

            if(mustEdge && components.Find(uEdge) == components.Find(vEdge)) {
                // Mandatory edges induces a cycle
                return -1;
            }

            if(components.Find(uEdge) != components.Find(vEdge)) {
                components.Union(uEdge, vEdge);
                treeEdges.push_back(i);
            }
        }

        // Checking if we have a spanning tree
        if(treeEdges.size() < n-1) return -1;

        // Computing the maximum stability
        // This first edge may be doubled
        int stability = 2*edges[treeEdges[0]][2];
        for(int i=treeEdges.size()-1; i>=0; --i) {
            const vector<int>& edge = edges[treeEdges[i]];
            int mustEdge = edge[3];
            int strengthEdge = edge[2];

            if(!mustEdge && k>0) {
                // Double the strength of the edge
                strengthEdge <<= 1;
                k--;
            }

            stability = min(stability, strengthEdge);
        }

        return stability;
    }
};
