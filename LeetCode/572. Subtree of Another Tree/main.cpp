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
    // Time: O(n + m)
    // Space: O(n + m)
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {

        const auto treeToString = [](this auto&& treeToString, string& str, TreeNode* root) -> void {
            // Base step
            if(!root) return;

            str += '(';
            treeToString(str, root->left);
            str += ',';
            str += to_string(root->val);
            str += ',';
            treeToString(str, root->right);
            str += ')';
        };

        string rootString;
        string subRootString;
        treeToString(rootString, root);
        treeToString(subRootString, subRoot);

        if(rootString.size() < subRootString.size()) return false;

        vector<int> pi(subRootString.size());
        // Compute the prefix function
        for(int i=1; i<subRootString.size(); ++i) {
            int j = pi[i-1];
            while(j > 0 && subRootString[i] != subRootString[j]) {
                j = pi[j-1];
            }
            if(subRootString[i] == subRootString[j]) {
                j++;
            }
            pi[i] = j;
        }
        // We match the strings
        int currentMatch = 0;
        for(int i=0; i<rootString.size(); ++i) {
            while(currentMatch > 0 && rootString[i] != subRootString[currentMatch]) {
                currentMatch = pi[currentMatch-1];
            }
            if(rootString[i] == subRootString[currentMatch]) {
                currentMatch++;
            }
            if(currentMatch == subRootString.size()) {
                return true;
            }
        }
        return false;
    }
};
