class Solution {
public:
    // TIme: O(n + ALPHA_SIZE log(ALPHA_SIZE))
    // SPace: O(ALPHA_SIZE)
    int minimumPushes(const string& word) {
        constexpr int ALPHA_SIZE = 26;
        vector<int> freq(ALPHA_SIZE);

        for(char c : word) {
            freq[c-'a']++;
        }
        vector<int> index(ALPHA_SIZE);
        iota(index.begin(), index.end(), 0);

        sort(index.begin(), index.end(),
            [&freq](int a, int b) -> bool {
                return freq[a] > freq[b];
            }
        );

        constexpr int FREE_KEYS = 8;
        int currWeight = 1;
        int currCount = 0;
        vector<int> weights (ALPHA_SIZE);
        for(int i=0; i<ALPHA_SIZE; ++i) {
            int letter = index[i];
            weights[letter] = currWeight;
            currCount++;
            if(currCount == FREE_KEYS) {
                currWeight++;
                currCount = 0;
            }
        }

        // Compute string cost
        int keysPressed = 0;
        for(int i=0; i<ALPHA_SIZE; ++i) {
            keysPressed += freq[i]*weights[i];
        }
        return keysPressed;
    }
};
