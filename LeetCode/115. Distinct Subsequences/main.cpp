class Solution {
public:
    // Time: O(nm)
    // Space: O(m)
    int numDistinct(string s, string t) {
        int n = s.size();
        int m = t.size();
        if(n < m) return 0;

        vector<unsigned long long> row(m);

        // Base case
        row[m-1] = (s[n-1]==t[m-1]) ? 1 : 0;
        
        // Recursive step
        for(int i=n-2; i>=0; --i) {
            for(int j=0; j<m-1; ++j) {
                unsigned long long ans = row[j];
                if(s[i]==t[j]) {
                    ans += row[j+1];
                }
                row[j] = ans;
            }

            // Base case
            if(s[i]==t[m-1]) {
                row[m-1]++;
            }
        }

        return row[0];
    }
};
