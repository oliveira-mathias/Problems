class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    char processStr(string s, long long k) {
        long long strSize = 0;
        // Computing the final size of the  string
        vector<bool> isNoOP(s.size(), true);
        for(int i=0; i<s.size(); ++i) {
            char c = s[i];
            switch(c) {
                case '*': {
                    if(strSize) {
                        strSize--;
                        isNoOP[i] = false;
                    }
                    break;
                }
                case '#': {
                    strSize *= 2;
                    isNoOP[i] = false;
                    break;
                }
                case '%': {
                    isNoOP[i] = false;
                    break;
                }
                default: {
                    isNoOP[i] = false;
                    strSize++;
                    break;
                }
            }
        }

        // We reverse the processing of the strin guntill we find the k-th character
        if(k >= strSize) return '.';
        for(int i=s.size()-1; i>=0; --i) {
            switch(s[i]) {
                case '*': {
                    if(!isNoOP[i]) strSize++;
                    break;
                }
                case '#': {
                    if(k >= strSize/2) {
                        k -= strSize/2;
                    }
                    strSize /= 2;
                    break;
                }
                case '%': {
                    k = strSize-1 - k;
                    break;
                }
                default: {
                    strSize--;
                    if(k==strSize) return s[i];
                    break;
                }
            }
        }
        // This return statement should never be reached
        return '.';
    }
};
