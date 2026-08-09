class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    vector<int> validSequence(string& word1, const string& word2) {
        vector<int> prefixDP(word1.size());
        vector<int> suffixDP(word1.size());

        // Computing DPs
        int val = 0;
        for(int i=0; i<word1.size(); ++i) {
            if(val < word2.size() && word1[i]==word2[val]) {
                val++;
            }
            prefixDP[i] = val;
        }
        val = 0;
        int currChar = word2.size() - 1;
        for(int i=word1.size()-1; i>=0; --i) {
            if(currChar >= 0 && word1[i]==word2[currChar]) {
                currChar--;
                val++;
            }
            suffixDP[i] = val;
        }

        // Choosing the update position
        int start = 0;
        while(start < word2.size() && word1[start]==word2[start]) {
            start++;
        }
        int pos = -1;
        if(start < word2.size()) {
            for(int i=start; i<word1.size(); ++i) {
                int openPrefix = (i > 0) ? prefixDP[i-1] : 0;
                int openSuffix = (i < word1.size()-1) ? suffixDP[i+1] : 0;
                if(openPrefix + openSuffix >= (word2.size()-1)) {
                    // This is the earliest char that can be modified
                    pos = i;
                    break;
                }
            }
        }
        char posChar = 0;
        if(pos >= 0) {
            posChar = word1[pos];
            word1[pos] = '*';
        }

        vector<int> ans;
        ans.reserve(word2.size());
        currChar = 0;
        for(int i=0; i<word1.size() && currChar<word2.size(); ++i) {
            if(word1[i]==word2[currChar] || word1[i]=='*') {
                ans.push_back(i);
                currChar++;
            }
        }

        if(pos >= 0) {
            word1[pos] = posChar;
        }

        if(ans.size() < word2.size()) ans.clear();
        return ans;
    }
};
