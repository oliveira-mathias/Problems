// n projects and its dependencies
vector<int> buildOrder(int n, const vector<pair<int, int>>& dep) {
  vector<vector<int>> adj(n, vector<int>());
  for(const auto [p1, p2] : dep) {
    // p2 must come after p1
    adj[p2].push_back(p1);
  }

  vector<int> ans;
  ans.reserve(n);
  enum status {
    NEW,
    VISITED,
    ON_STACK
  };
  vector<status> visited(n, NEW);
  auto DFS = [&adj, &ans, &visited](this auto&& DFS, int node) -> bool {
    visited[node] = ON_STACK;

    for(int neigh : adj[node]) {
      if(visited[neigh] == ON_STACK) {
        // We found a loop
        return false;
      }
      if(visited[neigh] == NEW) {
        bool subTreeStatus = DFS(neigh);
        // Subtree found a loop
        if(!subTreeStatus) return false;
      }
    }

    ans.push_back(node);
    visited[node] = VISITED;
    return true;
  };
  for(int i=0; i<n; ++i) {
    if(visited[i] == NEW) {
      // Return empty solution when we found a loop
      if(!DFS(i)) return vector<int>();
    }
  }
  return ans;
}
