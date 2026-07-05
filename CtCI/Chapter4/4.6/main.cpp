struct TreeNode {
  int val;
  TreeNode *left, *right, *parent;
  TreeNode(int _val, TreeNode* _parent) : val(_val), parent(_parent), left(nullptr), right(nullptr) {}
};

TreeNode* successor(TreeNode* node) {
  if(!node) return nullptr;


  TreeNode* childCandidate = node->right;
  if(childCandidate) {
    while(childCandidate->left) childCandidate = childCandidate->left;
    return childCandidate;
  }

  TreeNode* parent = node->parent;
  while(parent) {
    if(parent->left == node) {
      return parent;
    }
    node = parent;
    parent = parent->parent;
  }

  return nullptr;
}

int main() {}
