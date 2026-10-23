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

  bool searchWord(const string& word) {
    const auto searchWordRec = [&tree, &word](this auto&& searchWordRec, int wordIndex, int treeIndex) -> bool {
      // Base case
      if(wordIndex == word.size()) {
        return tree[treeIndex].isLeaf;
      }

      // Recursive case
      if(word[wordIndex] == '.') {
        for(int i=0; i<ALPHA_SIZE; ++i) {
          if(tree[treeIndex].child[i]) {
            if(searchWordRec(wordIndex+1, tree[treeIndex].child[i])) return true;
          }
        }
      }
      else {
        int letterIndex = word[wordIndex] - 'a';
        if(tree[treeIndex].child[letterIndex]) {
          return searchWordRec(wordIndex+1, tree[treeIndex].child[letterIndex]);
        }
      }

      return false;
    };
    return searchWordRec(0, 0);
  }

};
