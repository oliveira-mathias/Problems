class Solution {
public:
    // Time: O(n*m)
    // Space: O(min{n, m})
    int minimumDeleteSum(string& s1, string& s2) {
        bool swapped = false;
        if(s1.size() < s2.size()) {
            swap(s1, s2);
            swapped = true;
        }

        int n = s1.size();
        int m = s2.size();

        vector<int> currRow(m + 1);
        vector<int> nextRow(m + 1);

        // Basis step, Note nextRow[m] = 0
        for(int j=m-1; j>=0; --j) {
            nextRow[j] = s2[j] + nextRow[j+1];
        }

        for(int i=n-1; i>=0; --i) {
            currRow[m] = nextRow[m] + s1[i];

            for(int j=m-1; j>=0; --j) {
                int res;
                if(s1[i]==s2[j]) {
                    res = nextRow[j+1];
                }
                else {
                    res = min({s1[i] + nextRow[j], s2[j] + currRow[j+1]});
                }
                currRow[j] = res;
            }

            swap(currRow, nextRow);
        }

        if(swapped) {
            swap(s1, s2);
        }

        return nextRow[0];
    }
};
