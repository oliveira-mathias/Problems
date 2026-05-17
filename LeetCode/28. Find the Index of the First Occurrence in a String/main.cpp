class Solution {
public:
    int strStr(const string& haystack, const string& needle) {
        auto prefixFunction = [](const string& p) -> vector<int> {
            vector<int> pi(p.size());

            for(int i=1; i<p.size(); ++i) {
                int currLength = pi[i-1];
                while(currLength > 0 && p[currLength] != p[i])
                    currLength = pi[currLength-1];
                if(p[currLength] == p[i])
                    currLength++;
                pi[i] = currLength;
            }
            return pi;
        };
        auto matchPrefix = [](const vector<int>& pi, const string& s, const string& p) -> int {
            int piS = 0;
            int n = p.size();
            for(int i=0; i<s.size(); ++i) {
                while(piS > 0 && s[i] != p[piS])
                    piS = pi[piS -1];
                if(p[piS] == s[i])
                    piS++;
                if(piS==n) return i-n+1;
            }
            return -1;
        };
        vector<int> pi = prefixFunction(needle);
        return matchPrefix(pi, haystack, needle);
    }
};
