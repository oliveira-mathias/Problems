#include <vector>
#include <utility>

using namespace std;

struct Node {
  int val;
  vector<Node*> children;

  Node(int _val) : val(_val) {}
};

Node* FCA(Node* root, Node* n1, Node* n2) {
  if(n1 == n2) return n1;

  Node* FCANode = nullptr;
  bool foundFCA = false;
  int foundNodes = 0;
  auto DFS = [n1, n2, &FCANode, &foundFCA, &foundNodes](this auto&& DFS, Node* node) -> pair<bool, bool> {
    pair<bool, bool> status = {n1 == node, n2 == node};
    foundNodes += (n1 == node) + (n2 == node);

    // We only explore the subtree if at least one of the nodes hasn't been found
    if(foundNodes < 2) {
      for(Node* child : node->children) {
        // Early exit, there exists a single FCA and it has already been found
        if(foundFCA) break;

        auto [found1, found2] = DFS(child);
        status.first = status.first || found1;
        status.second =status.second || found2;
        if(status.first && status.second) {
          FCANode = node;
          foundFCA = true;
          // So that we only update FCANode once
          return {false, false};
        }
      }
    }

    return status;
  };

  DFS(root);
  // Return nullptr if there is no FCA
  return FCANode;
}

int main() {}
