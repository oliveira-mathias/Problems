class Solution {
public:
    // Time: O(n + m)
    // Space: O(n + m)
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> adj(numCourses, vector<int>());
        // Build the graph
        for(const vector<int>& edge : prerequisites) {
            int src = edge[0];
            int dest = edge[1];
            adj[src].push_back(dest);
        }

        enum class StackState {
            NONE,
            VISITED,
            ON_STACK
        };
        vector<StackState> visited(numCourses, StackState::NONE);
        const auto topoSort = [&adj, &visited](this auto&& topoSort, int node) -> bool {
            // Neighbors traversal
            visited[node] = StackState::ON_STACK;
            for(int neigh : adj[node]) {
                if(visited[neigh] == StackState::ON_STACK) {
                    return false;
                }
                else if(visited[neigh] == StackState::NONE) {
                    bool status = topoSort(neigh);
                    if(!status) return false;
                }
            }
            visited[node] = StackState::VISITED;

            return true;
        };
        for(int node=0; node<numCourses; ++node) {
            if(visited[node]==StackState::NONE) {
                bool status = topoSort(node);
                if(!status) return false;
            }
        }
        return true;
    }
};
