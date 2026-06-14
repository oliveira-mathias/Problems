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
    TreeNode* createBinaryTree(const vector<vector<int>>& descriptions) {
        // Each edge touches at most two nodes
        unordered_map<int, TreeNode*> nodes;
        unordered_set<int> childs;

        // Build the tree
        for(const vector<int>& edge : descriptions) {
            int parent = edge[0];
            int child = edge[1];
            int isLeft = edge[2];

            if(!nodes[parent]) nodes[parent] = new TreeNode(parent);
            if(!nodes[child]) nodes[child] = new TreeNode(child);
            if(isLeft) {
                nodes[parent]->left = nodes[child];
            }
            else {
                nodes[parent]->right = nodes[child];
            }
            childs.insert(child);
        }
        // Find the root
        // We remove the not roots nodes
        for(const auto& [key, node] : nodes) {
            if(!childs.contains(key)) return node;
        }
        // We should never get here
        return nullptr;
    }
};
