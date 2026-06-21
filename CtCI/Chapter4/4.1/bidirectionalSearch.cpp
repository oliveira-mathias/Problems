#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int shortRouteLen(vector<vector<int>>& adj, int start, int end) {
  int n = adj.size();

  queue<pair<int, int>> q;

  vector<int> distStart(n, -1);
  vector<int> distEnd(n, -1);

  distStart[start] = 0;
  distEnd[end] = 0;

  q.push({start, 0});
  q.push({end, 1});

  while(!q.empty()) {
    auto [node, branch] = q.front();
    q.pop();

    if(distStart[node] >= 0 && distEnd[node] >=0) {
      return distStart[node] + distEnd[node];
    }

    auto handleNeighs = [&adj, &q](vector<int>& dist, vector<int>& otherDist, int branch, int node) -> int {
      for(int child : adj[node]) {
        if(dist[child] < 0) {
          dist[child] = dist[node] + 1;

        if(dist[child] >= 0 && otherDist[child] >=0) {
          return dist[child] + otherDist[child];
        }
          q.push({child, branch});
        }
      }
      return -1;
    };
    int res = -1;
    if(branch) {
      res = handleNeighs(distEnd, distStart, 1, node);
    }
    else {
      res = handleNeighs(distStart, distEnd, 0, node);
    }
    // Early exit
    if(res >= 0) return res;
  }

  // Here the nodes aren't connected
  return -1;
}

int main() {
  vector<vector<int>> adj = {
    {3, 5},
    {2},
    {3, 1},
    {0, 2, 7, 4, 5},
    {6, 3},
    {6, 3},
    {4, 5},
    {3}
  };

  cerr << shortRouteLen(adj, 1, 6) << endl;
}
