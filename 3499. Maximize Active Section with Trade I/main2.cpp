class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int maxActiveSectionsAfterTrade(const string& s) {
        int currActive = 0;
        int delta = 0;
        int prevZeroBlock = 0;
        // Compute weights vector
        for(int i=0; i<s.size();) {
            int j;
            for(j=i; j<s.size() && s[i]==s[j]; ++j) {}
            if(s[i]=='1') {
                currActive += j-i;
            }
            else {
                if(prevZeroBlock > 0) {
                    delta = max(delta, prevZeroBlock + j-i);
                }
                prevZeroBlock = j-i;
            }
            i = j;
        }
        return currActive + delta;
    }
};
