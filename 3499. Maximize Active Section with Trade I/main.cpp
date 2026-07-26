class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int maxActiveSectionsAfterTrade(const string& s) {
        vector<int> weights;
        weights.reserve(s.size());

        int parity = (s[0]=='0') ? 0 : 1;
        int currActive = 0;
        // Compute weights vector
        for(int i=0; i<s.size();) {
            int j;
            for(j=i; j<s.size() && s[i]==s[j]; ++j) {}
            if(s[i]=='1') {
                currActive += j-i;
            }
            weights.push_back(j-i);
            i = j;
        }

        int delta = 0;
        for(int i=parity; i<weights.size(); i+=2) {
            // Processing a block of 0s
            if(i+2 < weights.size()) {
                // 010
                delta = max(delta, weights[i] + weights[i+2]);
            }
        }
        return currActive + delta;
    }
};
