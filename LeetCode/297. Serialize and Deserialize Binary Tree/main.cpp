/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:

    // Encodes a tree to a single string.
    // Time: O(n)
    // Space: O(H)
    string serialize(TreeNode* root) {
        // Early exit
        if(!root) return "";

        string ans;
        const auto DFS = [&ans](this auto&& DFS, TreeNode* node) -> void {
            // Base case
            if(!node) {
                return;
            }

            // Recursive case
            ans += "[";
            DFS(node->left);
            ans += "]";
            ans += to_string(node->val);
            ans += "[";
            DFS(node->right);
            ans += "]";
        };
        DFS(root);
        return ans;
    }

    // Decodes your encoded data to tree.
    // Time: O(n)
    // Space: O(n)
    TreeNode* deserialize(const string& data) {
        // Early exit
        if(data.empty()) return nullptr;

        vector<int> close(data.size());
        stack<int> s;
        for(int i=0; i<data.size(); ++i) {
            if(data[i]=='[') {
                s.push(i);
            }
            else if(data[i]==']') {
                int open = s.top();
                s.pop();
                close[open] = i;
            }
        }

        const auto buildTree = [&close, &data](this auto&& buildTree, int l, int r) -> TreeNode* {
            // Base case
            if(l > r) {
                return nullptr;
            }

            // Recursive step
            int numStart = close[l] + 1;
            int val = 0;
            int i = numStart;
            if(data[i]=='-') {
                ++i;
            }
            for(; data[i] != '['; ++i) {
                val = 10*val + (data[i]-'0');
            }
            if(data[numStart]=='-') {
                val *= -1;
            }

            TreeNode* node = new TreeNode(val);
            node->left = buildTree(l+1, close[l]-1);
            // Here i points to the start of the right side
            assert(close[i]);
            node->right = buildTree(i+1, close[i]-1);
            return node;
        };

        return buildTree(0, data.size()-1);
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
