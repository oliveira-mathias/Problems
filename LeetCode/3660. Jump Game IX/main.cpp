class Solution {
public:
    // Time: O(n log(n))
    // SPace: O(n)
    vector<int> maxValue(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> adj(n, vector<int>());
        vector<int> ans (n);

        // Compute edge to the left
        int currMax = numeric_limits<int>::min();
        int currMaxIndex = -1;
        for(int i=0; i<n; ++i) {
            if(nums[i] >= currMax) {
                currMax = nums[i];
                currMaxIndex = i;
            }
            else {
                adj[i].push_back(currMaxIndex);
            }   
        }

        // Compute edge to the right
        vector<int> suffixMin (n);
        suffixMin[n-1] = nums[n-1];
        for(int i=n-2; i>=0; --i) {
            // Update the min array
            suffixMin[i] = min(nums[i], suffixMin[i+1]);

            // Binary search the furthest smallest
            auto it = lower_bound(suffixMin.begin() + i, suffixMin.end(), nums[i]);
            int index = it - suffixMin.begin() -1;
            if(index > i) {
                adj[i].push_back(index);
            }
        }

        vector<int> orderedIndex;
        orderedIndex.reserve(n);
        for(int i=0; i<n; ++i) orderedIndex.push_back(i);
        sort(orderedIndex.begin(), orderedIndex.end(), [&nums](int i, int j) {
            return nums[i] > nums[j];
        });

        // We DFS the answer
        vector<bool> visited (n, false);
        auto DFS = [&adj, &visited, &ans](this auto&& DFS, int node, int value) {
            if(visited[node]) return;

            ans[node] = value;
            visited[node] = true;
            for(int neigh : adj[node]) {
                DFS(neigh, value);
                // To avoid cases in which teh dependency from the root is not direct
                ans[node] = max(ans[node], ans[neigh]);
            }
        };
        for(int index : orderedIndex) {
            if(visited[index]) continue;

            DFS(index, nums[index]);
        }
        return ans;
    }
};
