class Solution {
public:
    // Time: O(n)
    // SPace: O(n)
    string reverseParentheses(const string& s) {
        stack<int> st;
        vector<int> openParen(s.size());
        vector<int> closeParen(s.size());

        for(int i=0; i<s.size(); ++i) {
            if(s[i]=='(') {
                st.push(i);
            }
            else if(s[i]==')') {
                int start = st.top();
                st.pop();
                openParen[start] = i;
                closeParen[i] = start;
            }
        }

        string ans;
        ans.reserve(s.size());
        const auto builString = [&openParen, &closeParen, &ans, &s](this auto&& builString, int start, int end, bool isForward) -> void
        {
            if(isForward) {
                for(int i=start; i<=end;) {
                    if(s[i]=='(') {
                        int l = i+1;
                        int r = openParen[i] -1;
                        builString(l, r, !isForward);
                        i = openParen[i] + 1;
                    }
                    else {
                        ans += s[i];
                        ++i;
                    }
                }
            }
            else {
                for(int i=end; i>=start; ) {
                    if(s[i]==')') {
                        int l = closeParen[i] + 1;
                        int r = i-1;
                        builString(l, r, !isForward);
                        i = closeParen[i] - 1;
                    }
                    else {
                        ans += s[i];
                        --i;
                    }
                }
            }
        };
        builString(0, s.size()-1, true);
        return ans;
    }
};
