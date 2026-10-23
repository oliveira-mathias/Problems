class WordDictionary {
  public:
  static constexpr int ALPHA_SIZE = 26;
  
  private:
  struct TrieNode {
    int child[WordDictionary::ALPHA_SIZE] = {};
    bool isLeaf = false;

    void setIsLeaf() {
      isLeaf = true;
    }
  };
  vector<TrieNode> tree;
  
  public:
  WordDictionary() {
    // Add the sentinel
    tree.push_back(TrieNode());
  };
  void addWord(const string& s) {
    int currIndex = 0;
    for(char c : s) {
      int letterIndex = c-'a';
      if(!tree[currIndex].child[letterIndex]) {
        tree[currIndex].child[letterIndex] = tree.size();
        tree.push_back(TrieNode());
      }
      currIndex = tree[currIndex].child[letterIndex];
    }
    tree[currIndex].setIsLeaf();
  }

  bool search(const string& word) {
    struct StackInfo {
        int wordIndex;
        int treeIndex;
        int loopIndex;
    };
    stack<StackInfo> s;
    s.push({0,0,0});
    while(!s.empty()) {
        auto [wordIndex, treeIndex, loopIndex] = s.top();
        s.pop();

        // Base case
        if(wordIndex == word.size()) {
            if(tree[treeIndex].isLeaf) {
                return true;
            }
            continue;
        }

        if(word[wordIndex]=='.') {
            for(int i=loopIndex; i<ALPHA_SIZE; ++i) {
                if(tree[treeIndex].child[i]) {
                    // Push next state
                    s.push({wordIndex+1, tree[treeIndex].child[i], 0});
                }
            }
        }
        else {
            int letterIndex = word[wordIndex]-'a';
            if(tree[treeIndex].child[letterIndex]) {
                s.push({wordIndex+1, tree[treeIndex].child[letterIndex], 0});
            }
        }
    }
    return false;
  }

};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
