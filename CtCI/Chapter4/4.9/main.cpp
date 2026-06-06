#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {
  int val;
  Node* left;
  Node* right;
};

vector<vector<int>> BSTSequences(Node* root) {
  vector<vector<int>> ans;
  // Base case
  if(!root) return ans;

  if(!root->left && !root->right) {
    ans.push_back(vector<int>({root->val}));
    return ans;
  }

  // Recursive step
  if(!root->left || !root->right) {
    Node* child = (root->left) ? root->left : root->right;
    vector<vector<int>> childSequences = BSTSequences(child);
    for(const vector<int>& seq : childSequences) {
      ans.push_back(vector<int>());
      vector<int>& parentSeq = ans.back();
      parentSeq.resize(seq.size() + 1);
      parentSeq[0] = root->val;
      copy(seq.begin(), seq.end(), parentSeq.begin() + 1);
    }
    return ans;
  }

  auto interleave = [&ans, root](this auto&& interleave, const vector<int>& lSeq, const vector<int>& rSeq, vector<int>& lPos, int selected, int startVal) -> void
  {
    // Base case
    if(selected==lSeq.size()) {
      int lIndex = 0;
      int rIndex = 0;
      ans.push_back(vector<int>());
      vector<int>& s = ans.back();
      s.resize(1 + lSeq.size() + rSeq.size());
      s[0] = root->val;
      for(int i=1; i<1 + lSeq.size() + rSeq.size(); ++i) {
        if(lIndex<lPos.size() && i==lPos[lIndex]) {
          s[i] = lSeq[lIndex];
          lIndex++;
        }
        else {
          s[i] = rSeq[rIndex];
          rIndex++;
        }
      }
      return;
    }  

    // Recursive step
    for(int i=startVal; i<1 + lSeq.size() + rSeq.size(); ++i) {
      lPos[selected] = i;
      interleave(lSeq, rSeq, lPos, selected+1, i+1);
    }

  };
  vector<vector<int>> leftChildSeq = BSTSequences(root->left);
  vector<vector<int>> rightChildSeq = BSTSequences(root->right);
  for(const vector<int>& lSeq : leftChildSeq) {
    for(const vector<int>& rSeq : rightChildSeq) {
      vector<int> positions(lSeq.size());
      interleave(lSeq, rSeq, positions, 0, 1);
    }
  } 
  return ans;
}

int main() {
  Node n1 = {1, nullptr, nullptr};
  Node n3 = {3, nullptr, nullptr};
  Node n2 = {2, &n1, nullptr};
  Node n5 = {5, nullptr, nullptr};
  Node n4 = {4, &n2, &n5};

  vector<vector<int>> seqs = BSTSequences(&n4);
  for(const vector<int>& v : seqs) {
    for(int num : v) {
      cerr << num << " ";
    }
    cerr << endl;
  }
}
