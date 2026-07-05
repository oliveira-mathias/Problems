bool hasRoute(const vector<vector<int>>& adj, int node1, int node2) {
  int n = adj.size();

  vector<bool> visited(n, false);
  auto DFS = [&adj, &visited](this auto&& DFS, int node) -> void {
    visited[node] = true;

    for(int neigh : adj[node]) {
      if(!visited[neigh]) DFS(neigh);
    }
  };

  // Checking for node1 -> node2
  DFS(node1);
  if(visited[node2]) return true;
  
  // Checking for node2 -> node1
  fill(visited.begin(), visited.end(), false);
  DFS(node2);
  return visited[node1];
}

bool hasRouteBFS(const vector<vector<int>>& adj, int node1, int node2) {
  if(node1 == node2) return true;
  
  int n = adj.size();
  
  vector<int> visited(n, false);
  queue<int> q;

  visited[node1] = true;
  q.push(node1);

  while(!q.empty()) {
    int node = q.front();
    q.pop();

    for(int neigh : adj[node]) {
      if(neigh == node2) return true;
      if(!visited[neigh]) {
        visited[neigh] = true;
        q.push(neigh);
      }
    }
  }

  return false;
}
