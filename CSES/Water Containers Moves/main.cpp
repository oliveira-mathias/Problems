#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <functional>

using namespace std;

typedef pair<int, int> state;

int main() {
  int a, b, x;

  cin >> a >> b >> x;

  vector<vector<int>> moves(a+1, vector<int>(b+1));
  vector<vector<int>> dist(a+1, vector<int>(b+1, numeric_limits<int>::max()));
  vector<vector<state>> parent(a+1, vector<state>(b+1));
  priority_queue<pair<int, state>, vector<pair<int, state>>, greater<pair<int, state>>> pq;

  dist[0][0] = 0;
  parent[0][0] = {-1, -1};
  pq.push({0, {0,0}});
  while(!pq.empty()) {
    auto [nodeDist, node] = pq.top();
    auto [valA, valB] = node;
    pq.pop();

    if(nodeDist > dist[valA][valB]) continue;

    // Check the neighboring states
    const auto nextStates = [a, b](int nodeDist, int valA, int valB) -> vector<pair<int, state>> {
      vector<pair<int, state>> neighs(6);
      // MOVE1: FILL A
      neighs[0] = {nodeDist + a-valA, {a, valB}};
      // MOVE 2: FILL B
      neighs[1] = {nodeDist + b-valB, {valA, b}};
      // MOVE 3: EMPTY A
      neighs[2] = {nodeDist + valA, {0, valB}};
      // MOVE 4: EMPTY B
      neighs[3] = {nodeDist + valB, {valA, 0}};
      // MOVE 5: MOVE A B
      int toPass = min(valA, b-valB);
      neighs[4] = {nodeDist + toPass, {valA - toPass, valB + toPass}};
      // MOVE 6: MOVE B A
      toPass = min(valB, a-valA);
      neighs[5] = {nodeDist + toPass, {valA + toPass, valB - toPass}};
      return neighs;
    };
    int move = 0;
    for(auto [neighDist, neighState] : nextStates(nodeDist, valA, valB)) {
      auto [nextValA, nextValB] = neighState;
      if(neighDist < dist[nextValA][nextValB]) {
        dist[nextValA][nextValB] = neighDist;
        parent[nextValA][nextValB] = node;
        moves[nextValA][nextValB] = move;
        pq.push({neighDist, {nextValA, nextValB}});
      }
      move++;
    }
  }

  int minDist = numeric_limits<int>::max();
  state finalNode;
  if(a >= x) {
    for(int i=0; i<=b; ++i) {
      if(minDist > dist[x][i]) {
        minDist = dist[x][i];
        finalNode = {x, i};
      }
    }
  }

  // Checking if it is impossible to measure the water
  if(minDist == numeric_limits<int>::max()) {
    cout << -1 << endl;
    return 0;
  }

  // Build the solution
  const auto getMoveString = [](int move) -> string {
    switch(move) {
      case 0:
        return "FILL A";
      case 1:
        return "FILL B";
      case 2:
        return "EMPTY A";
      case 3:
        return "EMPTY B";
      case 4:
        return "MOVE A B";
      case 5:
        return "MOVE B A";
      default: return "";
    }
  };
  vector<string> sol;
  state aux = finalNode;
  while(aux != make_pair(0,0)) {
    int valA = aux.first;
    int valB = aux.second;

    sol.push_back(getMoveString(moves[valA][valB]));

    aux = parent[valA][valB];
  }
  cout << sol.size() << " " << dist[finalNode.first][finalNode.second] << endl;
  for(int i=sol.size()-1; i>=0; --i) {
    cout << sol[i] << endl;
  }

  

}
