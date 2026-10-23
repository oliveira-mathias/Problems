class Solution {
public:
    // Time: O(n)
    // Space: O(ALPHA_SIZE)
    string lexGreaterPermutation(const string& s, const string& target) {
        constexpr int ALPHA_SIZE = 26;
        int n = s.size();
        vector<int> freq(ALPHA_SIZE);
        for(char c : s) {
            freq[c-'a']++;
        }

        // We match the largest prefix
        string ans;
        ans.reserve(s.size());
        for(int i=0; i<target.size()-1; ++i) {
            if(freq[target[i]-'a']) {
                freq[target[i]-'a']--;
                ans += target[i];
            }
            else {
                break;
            }
        }

        // We find the largest feasible prefix
        bool foundBigger = false;
        while(!ans.empty()) {
            int nextCharIndex = ans.size();
            int targetNextChar = target[nextCharIndex]-'a';
            for(int j=targetNextChar+1; j<ALPHA_SIZE; ++j) {
                if(freq[j]) {
                    foundBigger = true;
                    break;
                }
            }

            if(foundBigger) {
                break;
            }
            // Here we move to the next state
            freq[ans.back()-'a']++;
            ans.pop_back();
        }

        // We try to append the bigger charaacter
        for(int i=target[ans.size()]-'a'+1; i<ALPHA_SIZE; ++i) {
            if(freq[i]) {
                freq[i]--;
                ans += i+'a';
                break;
            }
        }

        // If at this point ans is empty them there is no feasible permutation
        if(ans.empty()) return "";

        // Here we lay the remaining characters
        for(int i=0; i<ALPHA_SIZE; ++i) {
            while(freq[i]) {
                ans += i+'a';
                freq[i]--;
            }
        }

        return ans;
    }
};
