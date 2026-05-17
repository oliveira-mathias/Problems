class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    bool canReach(vector<int>& arr, int start) {
        vector<bool> visited (arr.size(), false);

        auto DFS = [&visited, &arr](this auto&& DFS, int node) -> bool {
            if(visited[node]) return false;

            visited[node] = true;
            if(arr[node] == 0) return true;

            // Checking neighbors
            bool result = false;
            if(node - arr[node] >= 0) result = DFS(node - arr[node]);
            if(node + arr[node] < arr.size()) result = result || DFS(node + arr[node]);
            return result;
        };

        return DFS(start);
    }
};
