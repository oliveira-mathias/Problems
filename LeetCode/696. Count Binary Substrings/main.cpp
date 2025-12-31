class Solution {
public:
    int countBinarySubstrings(string s) {
        int prevStreak = 0;
        int ans = 0;
        for(int i=0; i<s.size();) {
            int j = i;
            while(j < s.size() && s[j] == s[i]) {
                ++j;
            }
            ans += min(prevStreak, j - i);
            prevStreak = j - i;
            i = j;
        }   
        return ans;
    }
};
