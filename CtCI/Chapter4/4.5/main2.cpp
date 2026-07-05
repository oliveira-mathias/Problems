struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {} 
};

bool isBST(TreeNode* root) {
  auto isBSTRec = [](this auto&& isBSTRec, TreeNode* root, long long minRange, long long maxRange) {
    // Base case
    if(!root) return true;
    return (root->val >= minRange) && (root->val <= maxRange) && isBSTRec(root->left, minRange, root->val) && isBSTRec(root->right, root->val + 1LL, maxRange);
  };
  return isBSTRec(root, numeric_limits<int>::min(), numeric_limits<int>::max());
}
