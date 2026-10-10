class Solution {
public:
    // Time: O(n max{tokens[i].size()})
    // Space: O(n)
    int evalRPN(const vector<string>& tokens) {
        stack<int> st;
        for(const string& token : tokens) {
            if(token == "+" || token == "-" || token == "/" || token == "*") {
                int op2 = st.top();
                st.pop();
                int op1 = st.top();
                st.pop();
                if(token == "+") st.push(op1 + op2);
                if(token == "-") st.push(op1 - op2);
                if(token == "/") st.push(op1 / op2);
                if(token == "*") st.push(op1 * op2);
            }
            else {
                int num = stoi(token);
                st.push(num);
            }
            
        }
        return st.top();
    }
};
