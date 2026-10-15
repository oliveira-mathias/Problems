class Solution {
public:
    // Time: O(n)
    // Space: O(H)
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;

        // Early exit
        if(!root) return ans;

        const auto harvestLevel = [](this auto&& harvestLevel, vector<vector<int>>& layers, TreeNode* node, int level) -> void {
            // Allocating the level
            if(level >= layers.size()) {
                layers.push_back(vector<int>());
            }

            layers[level].push_back(node->val);

            // Recursive step
            if(node->left) {
                harvestLevel(layers, node->left, level+1);
            }
            if(node->right) {
                harvestLevel(layers, node->right, level+1);
            }
        };
        harvestLevel(ans, root, 0);
        return ans;
    }
};
