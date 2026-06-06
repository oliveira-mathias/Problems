class Trie {
    static constexpr int ALPHA_SIZE = 26;
    struct TrieNode {
        TrieNode* children[ALPHA_SIZE] = {};
        int witness = 0;

        ~TrieNode() {
            for(int i=0; i<ALPHA_SIZE; ++i) delete children[i];
        } 
    };

    TrieNode root;

    public:
    void insertContainer(const vector<string>& container) {
        for(int i=0; i<container.size(); ++i) {
            // Insert string container i
            const string& str = container[i];
            TrieNode* node = &root;

            if(str.size() < container[node->witness].size()) node->witness = i; 

            for(int j=str.size()-1; j>=0; --j) {
                int index = str[j]-'a';

                if(!node->children[index]) {
                    node->children[index] = new TrieNode();
                    node->children[index]->witness = i;
                }

                node = node->children[index];
                
                // Check if we update the witness of the current character node
                // The other untie criteria is handled by the iteration pattern
                if(str.size() < container[node->witness].size()) {
                    node->witness = i;
                }

            }
        }
    }

    int maxSuffixLength(const string& str) {
        TrieNode* node = &root;
        
        for(int j=str.size()-1; j>=0; --j) {
            int index = str[j]-'a';

            if(node->children[index]) {
                node = node->children[index];
            }
            else {
                return node->witness;
            }
        }

        return node->witness;
    }
};

class Solution {
public:
    // Time: O(Sum{wordsContainer[i].size()} + Sum{wordsQuery[i].size()})
    // Space: O(Sum{wordsContainer[i].size()})
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        Trie T;
        T.insertContainer(wordsContainer);
        
        vector<int> ans(wordsQuery.size());
        for(int i=0; i<wordsQuery.size(); ++i) {
            ans[i] = T.maxSuffixLength(wordsQuery[i]);
        }
        return ans;
    }
};
