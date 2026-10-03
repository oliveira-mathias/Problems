class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int longestValidParentheses(const string& s) {
        int maxSub = 0;
        int left = 0;
        int right = 0;
        // Forward traversal
        for(int i=0; i<s.size(); ++i) {
            if(s[i]=='(') {
                left++;
            }
            else {
                right++;
                if(right > left) {
                    left = 0;
                    right = 0;
                }
                else if(right == left) {
                    maxSub = max(maxSub, 2*left);
                }
            }
        }
        // Backward traversal
        left = 0;
        right = 0;
        for(int i=s.size()-1; i>=0; --i) {
            if(s[i]==')') {
                right++;
            }
            else {
                left++;
                if(left > right) {
                    left = 0;
                    right = 0;
                }
                else if(right == left) {
                    maxSub = max(maxSub, 2*left);
                }
            }
        }
        return maxSub;
    }
};
