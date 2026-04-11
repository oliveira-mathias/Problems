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
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        auto recursiveDiameter = [&diameter](this auto&& recursiveDiameter, TreeNode* root) -> int {
            if(!root) return 0;

            const int DepthLeft = recursiveDiameter(root->left);
            const int DepthRight = recursiveDiameter(root->right);

            int treeLargestPath = DepthLeft + DepthRight + 1;
            diameter = max(treeLargestPath, diameter);

            int treeDepth = 1 + max(DepthLeft, DepthRight);

            return treeDepth;
        };

        recursiveDiameter(root);
        return diameter-1;
    }
};
