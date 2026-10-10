class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minInsertions(const string& s) {
        int ops = 0;
        int balance = 0;
        for(int i=0; i<s.size(); ++i) {
            if(s[i]=='(') {
                balance++;
            }
            else {
                // Finde the group
                if(i+1 < s.size() && s[i+1]==')') {
                    ++i;
                }
                else {
                    // We need to make this single ')' a pair
                    ops++;
                }
                // Handle the group
                if(balance==0) {
                    // We need to insert previously a '('
                    ops++;
                }
                else {
                    // Here we consume a previously seen '('
                    balance--;
                }
            }
        }

        // We need to close the remaining '('
        ops += 2*balance;
        return ops;
    }
};
