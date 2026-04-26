class DSU {
    vector<int> root;
    vector<int> rank;

    public:
    DSU(int n) {
        root.reserve(n);
        for(int i=0; i<n; ++i) root[i] = i;

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
    // Time: O(n log(n))
    // Space: O(n)
    int minimumHammingDistance(vector<int>& source, vector<int>& target, vector<vector<int>>& allowedSwaps) {
        // Compute the connected components
        int n = source.size();

        DSU dsu(n);
        for(const vector<int>& swap : allowedSwaps) {
            dsu.Union(swap[0], swap[1]);
        }

        // Extracting the components
        unordered_map<int, vector<int>> sourceComponents, targetComponents;
        for(int i=0; i<n; ++i) {
            int root = dsu.Find(i);
            sourceComponents[root].push_back(source[i]);
            targetComponents[root].push_back(target[i]);
        }

        // Computing the minimum hamming distance
        int distance = 0;
        const auto computeDist = [](const vector<int>& v1, const vector<int>& v2) -> int {
            int equals = 0;
            for(int i=0, j=0; i<v1.size() && j<v2.size();) {
                if(v1[i] > v2[j]) {
                    ++j;
                }
                else if(v1[i] < v2[j]) {
                    ++i;
                }
                else {
                    ++j;
                    ++i;
                    ++equals;
                }
            }
            return v1.size() - equals;
        };
        for(auto& [key, sourceValues] : sourceComponents) {
            vector<int>& targetValues = targetComponents[key];

            sort(sourceValues.begin(), sourceValues.end());
            sort(targetValues.begin(), targetValues.end());

            distance += computeDist(sourceValues, targetValues);
        }

        return distance;
    }
};
