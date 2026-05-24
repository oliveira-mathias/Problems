string extractOrder(const vector<string>& dict) {
  // Collecting all letters
  unordered_set<int> letters;
  for(const string& s : dict) {
    for(char c : s) letters.insert(c-'a');
  }
  
  // Building the adjacency list
  constexpr int ALPHA_SIZE = 26;
  vector<vector<int>> adj(ALPHA_SIZE, vector<int>());
  for(int i=1; i<dict.size(); ++i) {
    const string& s1 = dict[i-1];
    const string& s2 = dict[i];
    // seach for the first position they differ
    int j;
    for(j=0; j<min(s1.size(), s2.size()) && s1[j] == s2[j]; ++j) {}

    // Extracting the edge
    if(j == min(s1.size(), s2.size())) {
      if(s1.size() > s2.size()) return ""; // inconsistent dict
    }
    else {
      // Here s1[j] < s2[j]
      adj[s1[j]-'a'].push_back(s2[j]-'a');
    }
  }

  // Constructing the ordering
  enum DFS_STATES {
    UNVISITED,
    ON_STACK,
    VISITED
  };
  vector<int> visited(ALPHA_SIZE, DFS_STATES::UNVISITED);
  string order;
  // Returns true if it have found a cycle
  const auto DFS = [&adj, &visited, &order](this auto&& DFS, int node) -> bool {
    if(visited[node] == DFS_STATES::ON_STACK) return true; // Here we found a loop
    if(visited[node] == DFS_STATES::VISITED) return false; // Already visited node

    // Here we are visiting the node for the first time
    visited[node] = DFS_STATES::ON_STACK;
    for(int neigh : adj[node]) {
      if(DFS(neigh)) return true;
    }
    order += node + 'a';
    visited[node] = DFS_STATES::VISITED;
    return false;
  };

  for(int letter : letters) {
    if(DFS(letter)) return "";
  }
  reverse(order.begin(), order.end());
  return order;
}
