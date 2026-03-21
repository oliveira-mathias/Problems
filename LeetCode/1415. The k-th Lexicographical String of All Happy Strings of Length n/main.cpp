class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    string getHappyString(int n, int k) {
        string ans;
        unsigned totalStrings = 3*(1U << (n-1));
        unsigned binSize = (1U << (n-1));

        if(k > totalStrings) return ans;

        // We will use zero indexing
        k--;

        // Choosing the first character
        ans += 'a' + (k / binSize);
        k = k%binSize;
        binSize >>= 1;
        unordered_map<char, vector<char>> options;
        options['a'] = vector<char>({'b', 'c'});
        options['b'] = vector<char>({'a', 'c'});
        options['c'] = vector<char>({'a', 'b'});

        // Appending the remaining characters
        while(binSize > 0) {
            int bin = k/binSize;
            ans += options[ans.back()][bin];
            k -= bin*binSize;
            binSize >>= 1;
        }

        return ans;

    }
};
