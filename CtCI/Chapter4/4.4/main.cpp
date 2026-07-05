struct TreeNode {
  int val;
  TreeNode *left, *right;

  TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

bool isBalanced(TreeNode* root) {
  bool isBalanced = true;
  // Returns the depth of the tree
  auto verifyBalanced = [&isBalanced](this auto&& verifyBalanced, TreeNode* root) -> int {
    // Base case
    if(!root || !isBalanced) return 0;

    // Recursive step
    int maxDepth = verifyBalanced(root->left);
    int minDepth = verifyBalanced(root->right);
    if(maxDepth < minDepth) swap(maxDepth, minDepth);

    if(maxDepth - minDepth > 1) {
      isBalanced = false;
    }

    return 1 + maxDepth;
  };

  verifyBalanced(root);
  return isBalanced;
}
