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
    // Time: O(n²)
    // Space: O(H)
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;

        // Early exit
        if(!root) return ans;

        const auto harvestLevel = [](this auto&& harvestLevel, vector<int>& layer, TreeNode* node, int level) -> bool {
            // Base case
            if(level == 0) {
                layer.push_back(node->val);
                return true;
            }

            // Recursive step
            bool inserted = false;
            if(node->left) {
                inserted = harvestLevel(layer, node->left, level-1);
            }
            if(node->right) {
                inserted |= harvestLevel(layer, node->right, level-1);
            }
            return inserted;

        };
        int level = 0;
        bool inserted = false;
        do {
            ans.push_back(vector<int>());
            vector<int>& layer = ans.back();
            inserted = harvestLevel(layer, root, level);

            if(!inserted) {
                ans.pop_back();
            }
            level++;
        } while(inserted);
        return ans;
    }
};
