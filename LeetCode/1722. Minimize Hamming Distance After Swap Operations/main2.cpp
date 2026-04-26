class DSU {
    vector<int> root;
    vector<int> rank;

    public:
    DSU(int n) {
        root.reserve(n);
        for(int i=0; i<n; ++i) root.push_back(i);

        rank = vector<int>(n);
    }

    int Find(int set) {
        if(set == root[set]) {
            return set;
        }
        return root[set] = Find(root[set]);
    }

    void Union(int set1, int set2) {
        int root1 = Find(set1);
        int root2 = Find(set2);

        if(root1 == root2) return;

        if(rank[root1] >= rank[root2]) {
            root[root2] = root1;

            if(rank[root1] == rank[root2]) rank[root1]++;
        }
        else {
            root[root1] = root2;
        }
    }
};

class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        // Compute the connected components
        int n = source.size();

        DSU dsu(n);
        for(const vector<int>& swap : allowedSwaps) {
            dsu.Union(swap[0], swap[1]);
        }

        // Extracting the components
        unordered_map<long long, int> frequency;
        for(int i=0; i<n; ++i) {
            long long root = dsu.Find(i);

            long long sourcePair = (root << 32) | source[i];
            frequency[sourcePair]++;

            long long targetPair =  (root << 32) | target[i];
            frequency[targetPair]--;
        }

        // Computing the minimum hamming distance
        int distance = 0;
        for(auto [_, freq] : frequency) {
            if(freq < 0) {
                distance += -freq;
            }
        }

        return distance;
    }
};
