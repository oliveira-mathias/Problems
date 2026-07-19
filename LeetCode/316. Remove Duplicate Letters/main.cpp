class Solution {
public:
    // Time: O(n)
    // Space: O(ALPHA_SIZE)
    string removeDuplicateLetters(const string& s) {
        constexpr int ALPHA_SIZE = 26;
        vector<int> freq(ALPHA_SIZE);
        vector<bool> inserted(ALPHA_SIZE);

        for(char c : s) {
            freq[c-'a']++;
        }

        string ans;
        for(int i=0; i<s.size(); ++i) {
            char letter = s[i];
            freq[letter-'a']--;
            if(!inserted[letter-'a']) {
                inserted[letter-'a'] = true;
                while(!ans.empty() && letter < ans.back() && freq[ans.back()-'a']) {
                    inserted[ans.back()-'a'] = false;
                    ans.pop_back();
                }
                ans += letter;
            }
        }
        return ans;
    }
};
