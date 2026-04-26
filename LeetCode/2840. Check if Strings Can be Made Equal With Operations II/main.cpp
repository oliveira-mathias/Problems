class Solution {
    static constexpr int alphaSize = 26;
public:
    // Time: O(n + alphaSize)
    // Space: O(alphaSize)
    bool checkStrings(const string& s1, const string& s2) {
        if(s1.size() != s2.size()) return false;

        vector<int> freqEven(alphaSize);
        vector<int> freqOdd(alphaSize);

        for(size_t i=0; i<s1.size(); ++i) {
            int indexS1 = s1[i] - 'a';
            int indexS2 = s2[i] - 'a';

            if(i & 1U) {
                freqOdd[indexS1]++;
                freqOdd[indexS2]--;
            }
            else {
                freqEven[indexS1]++;
                freqEven[indexS2]--;
            }
        }

        for(int i=0; i<alphaSize; ++i) {
            if(freqEven[i] || freqOdd[i]) {
                return false;
            }
        }

        return true;
    }
};
