class Trie {
    static constexpr int ALPHA_SIZE = 26;

    struct Node {
        int child[ALPHA_SIZE] = {};
        string value = "?";
    };

    vector<Node> tree;
    
    public:
    Trie() {
        // We push back a sentinel Node
        tree.push_back(Node());
    }
    void insertNode(const string& key, const string& value) {
        int currIndex = 0;
        for(char c : key) {
            int cIndex = c-'a';
            if(!(tree[currIndex].child[cIndex])) {
                tree.push_back(Node());
                tree[currIndex].child[cIndex] = tree.size() - 1;
            }
            currIndex = tree[currIndex].child[cIndex];
        }
        // We insert the key
        tree[currIndex].value = value;
    }

    string queryNode(const string& key) {
        int currIndex = 0;
        for(char c : key) {
            int cIndex = c-'a';
            if(!(tree[currIndex].child[cIndex])) {
                // We did not found the key
                return "?";
            }
            currIndex = tree[currIndex].child[cIndex];
        }
        return tree[currIndex].value;
    }

};

class Solution {
public:
    // Time: O(n + m)
    // Space: O(n + m)
    string evaluate(const string s, const vector<vector<string>>& knowledge) {
        // Creating the dictionary
        Trie T;
        for(const vector<string>& item : knowledge) {
            const string& key = item[0];
            const string& value = item[1];
            T.insertNode(key, value);
        }

        string ans;
        ans.reserve(s.size());
        string pattern;
        // Max key size is 10
        pattern.reserve(10);
        for(int i=0; i<s.size();) {
            if(s[i]=='(') {
                pattern.clear();
                int j=i+1;
                for(; s[j] != ')' && j<s.size(); ++j) {
                    pattern += s[j];
                }
                ans += T.queryNode(pattern);
                // j is in the ')' position
                i = j+1;
            }
            else {
                ans += s[i];
                i++;
            }
        }
        return ans;
    }
};
