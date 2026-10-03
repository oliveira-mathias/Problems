class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int longestValidParentheses(const string& s) {
        stack<int> st;
        vector<int> prevMountain(s.size(), -1);
        int maxSubStr = 0;
        for(int i=0; i<s.size(); ++i) {
            if(s[i]=='(') {
                st.push(i);
            }
            // Here s[i] must be ')'
            else {
                if(!st.empty()) {
                    int start = st.top();
                    st.pop();
                    // Try to concatenate with previous mountain
                    if(start > 0 && prevMountain[start-1] >= 0) {
                        start = prevMountain[start-1];
                    }
                    prevMountain[i] = start;
                    maxSubStr = max(maxSubStr, i - start + 1);
                }
            }
        }
        return maxSubStr;
    }
};
