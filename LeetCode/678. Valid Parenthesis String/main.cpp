class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    bool checkValidString(const string& s) {
        int lBalance = 0;
        int rBalance = 0;
        for(char c :  s) {
            if(c=='(') {
                lBalance++;
                rBalance++;
            }
            else if(c==')') {
                lBalance = max(0, lBalance-1);
                rBalance--;
                if(rBalance < 0) return false;
            }
            // Here we must have a '*'
            else {
                lBalance = max(0, lBalance-1);
                rBalance++;
            }
        }

        return lBalance==0;
    }
};
