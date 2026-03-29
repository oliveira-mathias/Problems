class Solution {
public:
    // Time: O(n²)
    // Space: O(1)
    string findTheString(vector<vector<int>>& lcp) {
        int n = lcp.size();

        // Check for symetry and DP consistency
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                // Symetry check
                if(lcp[i][j] != lcp[j][i]) {
                    return "";
                }

                // DP consistency check
                if(i==n-1 || j==n-1) {
                    if(lcp[i][j] != 0 && lcp[i][j] != 1) {
                        return "";
                    }
                }
                else {
                    if(lcp[i][j] != 0 && lcp[i][j] != lcp[i+1][j+1] + 1) {
                        return "";
                    }
                }
            }
        }

        // We create a candidate
        string res(n, 0);
        char current = 'a';
        for(int i=0; i<n; ++i) {
            if(!res[i]) {
                // We can only use lower case charaacters
                if(current > 'z') return "";
                for(int j=i; j<n; ++j) {
                    if(lcp[i][j] > 0) {
                        res[j] = current;
                    }
                }
                current++;
            }
        }


        // We validate the candidate
        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                if((lcp[i][j] > 0 && res[i] != res[j]) || (lcp[i][j]==0 && res[i] == res[j])) {
                    return "";
                }
            }
        }

        return res;
    }
};
