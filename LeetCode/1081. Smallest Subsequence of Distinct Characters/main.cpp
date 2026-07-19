class Solution {
public:
    // Time: O(n*ALPHA_SIZE + ALPHA_SIZE³)
    // Space: O(n*ALPHA_SIZE)
    string smallestSubsequence(const string& s) {
        constexpr int ALPHA_SIZE = 26;
        int n = s.size();

        // DP tables
        vector<vector<int>> uniques(n+1, vector<int>(ALPHA_SIZE));
        vector<vector<int>> firstSeen(n+1, vector<int>(ALPHA_SIZE));

        // Base step
        fill(firstSeen[n].begin(), firstSeen[n].end(), n);
        int uniqueChars = 0;

        for(int i=n-1; i>=0; --i) {
            int currChar = s[i]-'a';
            uniques[i] = uniques[i+1];
            firstSeen[i] = firstSeen[i+1];

            if(!uniques[i][currChar]) {
                ++uniqueChars;
            }
            uniques[i][currChar] = 1;
            firstSeen[i][currChar] = i;
        }

        string ans;
        ans.reserve(uniqueChars);
        int currIndex = 0;
        while(currIndex < n && uniqueChars) {
            // Select the smallest feasible char
            int selectedChar;
            for(selectedChar=0; selectedChar<ALPHA_SIZE; ++selectedChar) {
                if(uniques[currIndex][selectedChar]) {
                    int target = firstSeen[currIndex][selectedChar] + 1;
                    vector<int>& nextRow = uniques[target];

                    // Exclude already chosen chars from candidate row
                    for(char c : ans) {
                        nextRow[c-'a'] = 0;
                    }
                    nextRow[selectedChar] = 0;

                    // How many uniques there are on the nextRow
                    int nextRowUniques = 0;
                    for(int i=0; i<ALPHA_SIZE; ++i) {
                        if(nextRow[i] > 0) nextRowUniques++;
                    }

                    // Here we know that we can jump andstill complete the sequence
                    if(nextRowUniques >= uniqueChars-1) break;
                    nextRow[selectedChar] = 1;
                }
            }
            assert(selectedChar < ALPHA_SIZE);

            ans += 'a' + selectedChar;
            currIndex = firstSeen[currIndex][selectedChar] + 1;
            uniqueChars--;
        }
        return ans;
    }
};
