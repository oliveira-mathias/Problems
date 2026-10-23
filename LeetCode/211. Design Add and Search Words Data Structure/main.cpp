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
    vector<TrieNode>& trie = tree;
    const auto searchWordRec = [&trie, &word](this auto&& searchWordRec, int wordIndex, int treeIndex) -> bool {
      // Base case
      if(wordIndex == word.size()) {
        return trie[treeIndex].isLeaf;
      }

      // Recursive case
      if(word[wordIndex] == '.') {
        for(int i=0; i<ALPHA_SIZE; ++i) {
          if(trie[treeIndex].child[i]) {
            if(searchWordRec(wordIndex+1, trie[treeIndex].child[i])) return true;
          }
        }
      }
      else {
        int letterIndex = word[wordIndex] - 'a';
        if(trie[treeIndex].child[letterIndex]) {
          return searchWordRec(wordIndex+1, trie[treeIndex].child[letterIndex]);
        }
      }

      return false;
    };
    return searchWordRec(0, 0);
  }

};


/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
