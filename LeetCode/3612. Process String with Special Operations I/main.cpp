class Solution {
public:
    string processStr(string s) {
        string res;
        for(char c : s) {
            switch(c) {
                case '*': 
                    if(res.size()) res.pop_back();
                    break;
                case '#':
                    res += res;
                    break;
                case '%':
                    reverse(res.begin(), res.end());
                    break;
                default:
                    res += c;
                    break;
            }
        }
        return res;
    }
};
