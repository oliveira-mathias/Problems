class Solution {
public:
    // Time: O(n * NUM_INT * (lo{n} + log{NUM_INT}))
    // Space: O(n * NUM_INT²)
    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        constexpr int LEFT = 0;
        constexpr int RIGHT = 1;
        constexpr int WEIGHT = 2;
        int n = intervals.size();
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);
        // Sort intervals by start point
        sort(index.begin(), index.end(), 
        [&intervals](int a, int b) {
            const vector<int>& vecA = intervals[a];
            const vector<int>& vecB = intervals[b];
            return vecA[LEFT] < vecB[LEFT];
        });

        constexpr int NUM_INT = 4;
        vector<vector<long long>> DP(NUM_INT+1, vector<long long>(n));
        vector<vector<vector<int>>> DPVec(NUM_INT+1, vector<vector<int>>(n, vector<int>()));
        
        const auto UpperBound = [&intervals, &index, n, LEFT](int j, int right)  -> int {
            int l = j+1;
            int r = n;
            while(l < r) {
                int m = l + (r-l)/2;
                if(intervals[index[m]][LEFT] > right) {
                    r = m;
                }
                else {
                    l = m+1;
                }
            }
            return l;
        };
        // Recursive case
        for(int i=1; i<=NUM_INT; ++i) {
            for(int j=n-1; j>=0; --j) {
                int right = intervals[index[j]][RIGHT];
                int weight = intervals[index[j]][WEIGHT];

                // We don't pick interval j but still uses i intervals
                long long option1 = (j < n-1) ? DP[i][j+1] : 0;
                vector<int> vecOption1 = (j < n-1) ? DPVec[i][j+1] : vector<int>();
                // We don't use i intervals
                long long option2 = DP[i-1][j];
                vector<int> vecOption2 = DPVec[i-1][j];
                // We pick interval j and use i intervals
                int l = UpperBound(j, right);

                // Here l is the first feasible interval index
                long long option3 = weight + ((l < n) ? (DP[i-1][l]) : 0);
                vector<int> vecOption3 = (l < n) ? (DPVec[i-1][l]) : vector<int>();
                vecOption3.push_back(index[j]);
                sort(vecOption3.begin(), vecOption3.end());

                DP[i][j] = max(option1, max(option2, option3));
                vector<int> ans;
                if(option1 == DP[i][j]) {
                    ans = vecOption1;
                }
                if(option2 == DP[i][j]) {
                    if(ans.empty() || vecOption2 < ans) {
                        ans = vecOption2;
                    }
                }
                if(option3 == DP[i][j]) {
                    if(ans.empty() || vecOption3 < ans) {
                        ans = vecOption3;
                    }
                }
                DPVec[i][j] = ans;
            }
        }
        return DPVec[NUM_INT][0];
    }
};
