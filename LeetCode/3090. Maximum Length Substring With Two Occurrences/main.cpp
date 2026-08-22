class Solution {
public:
    // Time: O(n)
    // Space: O(ALPHA_SIZE)
    int maximumLengthSubstring(const string& s) {
        constexpr int ALPHA_SIZE = 26;
        int freq[ALPHA_SIZE] = {};

        int maxSize = 0;
        for(int l=0, r=0; r < s.size(); r++) {
            int currChar = s[r]-'a';
            freq[currChar]++;

            // The only entry that can be greater than or equal to 2 is currChar
            while(freq[currChar] > 2) {
                int lChar = s[l]-'a'; 
                freq[lChar]--;
                l++;
            }

            // Here we have a valid window
            maxSize = max(maxSize, r-l+1);
        }
        return maxSize;
    }
};
