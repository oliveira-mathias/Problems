#include <vector>
#include <utility>

using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;

  Node(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

Node* FCA(Node* root, Node* n1, Node* n2) {
  if(!root || !n1 || !n2) return nullptr;
  if(n1 == n2) return n1;

  auto DFS = [n1, n2](this auto&& DFS, Node* node) -> Node* {
    // We don't check the subtree if we hit one of the nodes
    if(!node || node == n1 || node == n2) return node;

    // Or we bubble up the FCA or we encounters two FCA in such case
    // node is the FCA
    Node* FCANode = nullptr;
    int foundFCA = 0;
    
    Node* candidate1 = DFS(node->left);
    if(candidate1) {
      FCANode = candidate1;
      foundFCA++;
    }

    Node* candidate2 = DFS(node->right);
    if(candidate2) {
      FCANode = candidate2;
      foundFCA++;
    }

    return (foundFCA == 2) ? node : FCANode;
  };

  // We assume both nodes are on the tree
  return DFS(root);
}

int main() {}
