class Solution {
public:
    // Time: O(n²)
    // Space: O(ALPHA_SIZE)
    string lexGreaterPermutation(const string& s, const string& target) {
        constexpr int ALPHA_SIZE = 26;
        int n = s.size();
        vector<int> freq(ALPHA_SIZE);
        for(char c : s) {
            freq[c-'a']++;
        }

        string ans;
        ans.reserve(s.size());
        vector<int> auxFreq(ALPHA_SIZE);
        // The structure of the solution is
        // [commonPrefix | greater char | sorted suffix]
        // We will just brute the size of the commom prefix
        for(int prefix=n-2; prefix>=-1; --prefix) {
            // Reseting the state
            copy(freq.begin(), freq.end(), auxFreq.begin());
            ans.clear();

            // Build the common Prefix
            for(int i=0; i<=prefix; ++i) {
                int targetIndex = target[i]-'a';
                if(auxFreq[targetIndex]) {
                    ans += target[i];
                    auxFreq[targetIndex]--;
                }
                else {
                    // Here we can't continue the prefix
                    break;
                }
            }
            // Surely we will need a new prefix size
            if(ans.size() < prefix+1) continue;

            // Here we need to find a greater character
            bool insertedBigger = false;
            for(int j=target[prefix+1]-'a'+1; j<ALPHA_SIZE; ++j) {
                if(auxFreq[j]) {
                    auxFreq[j]--;
                    insertedBigger = true;
                    ans += j+'a';
                    break;
                }
            }

            if(!insertedBigger) {
                // Surely we will need a new prefix size
                continue;
            }

            // Append the remaining characters in sorted order
            for(int j=0; j<ALPHA_SIZE; ++j) {
                while(auxFreq[j]) {
                    ans += j+'a';
                    auxFreq[j]--;
                }
            }

            // Here we successfully built the desired string
            return ans;
        }
        // Here there is no such permutation
        return "";
    }
};
