class Solution {
public:
    static constexpr int NEUTRALIZATIONS = 2;
    // Time: O(nmk)
    // Space: O(mk)
    int maximumAmount(const vector<vector<int>>& coins) {
        int n = coins.size();
        int m = coins[0].size();
        vector<vector<int>> DP(NEUTRALIZATIONS+1, vector<int>(m+1));
        vector<vector<int>> DPPrev(NEUTRALIZATIONS+1, vector<int>(m+1, numeric_limits<int>::min()));

        for(int i=n-1; i>=0; --i) {
            for(int k=0; k<=NEUTRALIZATIONS; ++k) {
                for(int j=m-1; j>=0; --j) {
                    if(i==n-1 && j==m-1) {
                        if(k==0) {
                            DP[k][j] = coins[i][j];
                        }
                        else {
                            DP[k][j] = max(0, coins[i][j]);
                        }

                        continue;
                    }
                    
                    int largestPath = numeric_limits<int>::min();
                    if(i < n-1) {
                        largestPath = max(largestPath, DP[k][j]);
                    }
                    if(j < m-1) {
                        largestPath = max(largestPath, DP[k][j+1]);
                    }
                    int option1 = coins[i][j] + largestPath;
                    int option2 = numeric_limits<int>::min();
                    if(coins[i][j] < 0 && k>0) {
                        if(i < n-1) {
                            option2 = max(option2, DPPrev[k-1][j]);
                        }
                        if(j < m-1) {
                            option2 = max(option2, DP[k-1][j+1]);
                        }
                    }

                    DP[k][j] = max(option1, option2);
                }

            }
            copy(DP.begin(), DP.end(), DPPrev.begin());
        }

        return DPPrev[NEUTRALIZATIONS][0];

    }
};
