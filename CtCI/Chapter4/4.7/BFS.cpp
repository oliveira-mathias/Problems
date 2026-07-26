// n projects and its dependencies
vector<int> buildOrder(int n, const vector<pair<int, int>>& dep) {
  vector<vector<int>> adj(n, vector<int>());
  vector<int> inDegree(n);
  for(const auto [p1, p2] : dep) {
    // p1 must come before p2
    adj[p1].push_back(p2);
    inDegree[p2]++;
  }

  queue<int> q;
  for(int i=0; i<n; ++i) {
    if(!inDegree[i]) {
      q.push(i);
    }
  }

  vector<int> ans;
  ans.reserve(n);
  while(!q.empty()) {
    int node = q.front();
    q.pop();
    ans.push_back(node);

    for(int neigh : adj[node]) {
      inDegree[neigh]--;
      if(!inDegree[neigh]) q.push(neigh);
    }
  }

  return (ans.size()==n) ? ans : vector<int>();
}
