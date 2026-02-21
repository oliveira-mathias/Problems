class Solution {
    string buildStringRec(string& s, int start, int end) {
        // Base case
        if(start + 1 == end) {
            return "10";
        }

        string ans;
        ans.reserve(end - start + 1);

        // Recursive step
        // Collecting mountains
        vector<string> mountainStrings;
        int delta = 0;
        int rangeStart = start;
        for(int i=start; i <= end; ++i) {
            delta += (s[i]=='1') ? 1 : -1;

            // Here we found a mountain
            if(i > rangeStart && delta == 0) {
                // Processing this mountain
                string intervalAns;
                intervalAns.reserve(i - rangeStart + 1);

                intervalAns += s[rangeStart];
                if(rangeStart+1 < i-1) {
                    intervalAns += buildStringRec(s, rangeStart+1, i-1);
                }
                intervalAns += s[i];

                mountainStrings.emplace_back(std::move(intervalAns));

                // Updating variables for next iteration
                delta = 0;
                rangeStart = i+1;
            }
        }

        // Sort mountain strings
        sort(mountainStrings.begin(), mountainStrings.end(), greater<string>());

        for(string& mountain : mountainStrings) {
            ans += mountain;
        }

        return ans;
    }
public:
    // Time: O(n³ log(n))
    // Space: O(n²)
    string makeLargestSpecial(string s) {
        return buildStringRec(s, 0, s.size()-1);
    }
};
