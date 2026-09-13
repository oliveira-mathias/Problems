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
    int averageOfSubtree(TreeNode* root) {
        if(!root) return 0;

        const auto averageOfSubtreeRec = [](this auto&& averageOfSubtreeRec, TreeNode* root, int& ans) -> pair<int, int> {
            // Base case
            if(!root) return {0,0};

            // Recursive case
            auto [leftSum, leftNumNodes] = averageOfSubtreeRec(root->left, ans);
            auto [rightSum, rightNumNodes] = averageOfSubtreeRec(root->right, ans);

            int nodeSum = leftSum + root->val + rightSum;
            int nodeNumNodes = leftNumNodes + 1 + rightNumNodes;

            // Here we track that the node is equal tothe averaage of its subtree
            if(nodeSum/nodeNumNodes == root->val) {
                ans++;
            }

            return {nodeSum, nodeNumNodes};
        };
        int ans = 0;
        averageOfSubtreeRec(root, ans);

        return ans;
    }
};
