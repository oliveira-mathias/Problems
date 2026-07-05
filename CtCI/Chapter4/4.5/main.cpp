struct TreeNode {
  int val;
  TreeNode *left, *right;
  TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {} 
};

bool isBST(TreeNode* root) {
  if(!root) return true;

  bool isBST = true;
  auto isBSTRec = [&isBST](this auto&& isBSTRec, TreeNode* root) -> pair<int, int> {
    int minRange = root->val; 
    int maxRange = root->val;
    
    if(root->left) {
      auto [minLeftRange, maxLeftRange] = isBSTRec(root->left);
      // Early exit check
      if(!isBST || maxLeftRange > root->val) {
        isBST = false;
        return {-1, -1};
      }
      minRange = minLeftRange;
    }
    if(root->right) {
      auto [minRightRange, maxRightRange] = isBSTRec(root->right);
      // Early exit check
      if(!isBST || minRightRange < root->val) {
        isBST = false;
        return {-1, -1};
      }
      maxRange = maxRightRange;
    }

    return {minRange, maxRange};
  };
  isBSTRec(root);
  return isBST;
}
