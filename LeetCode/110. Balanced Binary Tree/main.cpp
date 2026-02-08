/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    bool isBalanced(TreeNode* root) {
        auto isBalancedRec = [](auto&& self, TreeNode* root) -> pair<bool, int> {
            // Base case
            if(!root) {
                return make_pair(true, 0);
            }

            // Recursive step
            const auto [isLeftBalanced, leftDepth] = self(self, root->left);
            const auto [isRightBalanced, rightDepth] = self(self, root->right);

            bool isRootBalanced = isLeftBalanced && isRightBalanced && (abs(leftDepth - rightDepth) <= 1);
            int rootDepth = 1 + max(leftDepth, rightDepth);
            
            return make_pair(isRootBalanced, rootDepth);
        };

        const auto [isRootBalanced, rootDepth] = isBalancedRec(isBalancedRec, root);
        return isRootBalanced;
    }
};
