class Solution {
public:
    // Time: O(n²)
    // SPace: O(n)
    string reverseParentheses(string s) {
        stack<int> openParen;
        for(int i=0; i<s.size(); ++i) {
            if(s[i]=='(') {
                openParen.push(i);
            }
            else if(s[i]==')') {
                int start = openParen.top();
                openParen.pop();
                reverse(s.begin() + start, s.begin() + i+1);
            }
        }

        string ans;
        ans.reserve(s.size());
        // Removing the parenthesis
        for(char c : s) {
            if(c != '(' && c != ')') {
                ans += c;
            }
        }
        return ans;
    }
};
