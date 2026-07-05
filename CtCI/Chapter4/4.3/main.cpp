struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;

  TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

struct ListNode {
  ListNode* next;
  TreeNode* val;

  ListNode(TreeNode* _val) : val(_val), next(nullptr) {}
};

// Time: O(n)
// Space: O(n)
vector<ListNode*> buildLayers(TreeNode* root) {
  vector<ListNode*> res;

  if(!root) return res;

  ListNode aux(nullptr);
  ListNode* tail = &aux;
  int currentDepth = 0;
  queue<pair<int, TreeNode*>> q;
  q.push({0, root});

  while(!q.empty()) {
    auto [depth, node] = q.front();
    q.pop();

    // flush the previous layer
    if(depth > currentDepth) {
      res.push_back(aux.next);
      aux.next = nullptr;
      tail = &aux;
      currentDepth++;
    }

    // Insert node in current layer
    tail->next = new ListNode(node);
    tail = tail->next;

    // Insert childs in next layer
    if(node->left) {
      q.push({depth + 1, node->left});
    }
    if(node->right) {
      q.push({depth + 1, node->right});
    }

  }

  // Adding the last layer to the vector
  res.push_back(aux.next);
  return res;

}
