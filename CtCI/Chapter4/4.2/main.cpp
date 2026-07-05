struct Node {
  int val;
  Node* left;
  Node* right;

  Node(int _val) : val(_val), left(nullptr), right(nullptr) {} 
};

// Time: O(n)
// Space: O(log(n))
Node* buildTree(const vector<int>& arr) {
  auto buildTreeRec = [&arr](this auto&& buildTreeRec, int l, int r) -> Node* {
    if(l > r) return nullptr;

    int m = l + (r-l)/2;
    Node* root = new Node(arr[m]);
    root->left = buildTreeRec(l, m-1);
    root->right = buildTreeRec(m+1, r);
    return root;
  };

  if(arr.empty()) return nullptr;
  return buildTreeRec(0, arr.size()-1);
}
