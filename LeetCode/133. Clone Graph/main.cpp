/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};
*/

class Solution {
public:
    // Time: O(n + m)
    // Space: O(n)
    Node* cloneGraph(Node* node) {
        if(!node) return nullptr;

        unordered_map<Node*, Node*> nodes;
        const auto deepCopy = [&nodes](this auto&& deepCopy, Node* node) -> Node* {
            // Base case
            auto it = nodes.find(node);
            if(it != nodes.end()) {
                return it->second;
            }

            // Recursive case
            Node* nodeCopy = new Node(node->val);
            nodes[node] = nodeCopy;

            for(Node* neigh : node->neighbors) {
                (nodeCopy->neighbors).push_back(deepCopy(neigh));
            }

            return nodeCopy;
        };

        return deepCopy(node);
    }
};
