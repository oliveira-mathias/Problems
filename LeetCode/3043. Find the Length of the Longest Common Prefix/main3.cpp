class Trie {
    static constexpr int NUM_DIGITS = 10;

    struct TrieNode {
      TrieNode* child[NUM_DIGITS] = {};

      ~TrieNode() {
        for(int i=0; i<NUM_DIGITS; ++i) delete child[i];
      }
    };

    TrieNode root;

    public:
    void addString(const string& s) {
        TrieNode* node = &root;
        for(int i=0; i<s.size(); ++i) {
            int digit = s[i] - '0';
            if(!node->child[digit]) {
                node->child[digit] = new TrieNode();
            }
            node = node->child[digit];
        }
    }

    int longestPrefix(const string& s) {
        TrieNode* node = &root;
        for(int i=0; i<s.size(); ++i) {
            int digit = s[i] - '0';
            if(!node->child[digit]) return i;
            node = node->child[digit];
        }
        return s.size();
    }

};

class Solution {
public:
    // Time: O(n + m)
    // Space: O(n)
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        Trie T;
        for(int num : arr1) {
            T.addString(to_string(num));
        }

        int maxPrefix = 0;
        for(int num : arr2) {
            maxPrefix = max(maxPrefix, T.longestPrefix(to_string(num)));
        }
        return maxPrefix;
    }
};
