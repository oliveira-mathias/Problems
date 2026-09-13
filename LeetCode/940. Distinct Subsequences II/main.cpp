class Solution {
public:
    // Time: O(n)
    // Space: O(ALPHA_SIZE)
    int distinctSubseqII(const string& s) {
        constexpr int ALPHA_SIZE = 26;
        constexpr int MOD = 1000000007;
        vector<int> prevTotal(ALPHA_SIZE);

        // We start with the empty string
        int currTotal = 1;
        for(char c : s) {
            int index = c-'a';
            int newTotal = (2*currTotal) % MOD;
            newTotal -= prevTotal[index];
            if(newTotal < 0) {
                newTotal += MOD;
            }
            prevTotal[index] = currTotal;
            currTotal = newTotal;
        }
        // We remove the empty string from the computation
        return currTotal ? (currTotal-1) : (MOD-1);
    }
};
