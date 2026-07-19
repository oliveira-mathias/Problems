class Solution {
public:
    // et M = max{nums[i]}
    // Time: O(M*log(M) + Q*log(M))
    // Space: O(M)
    vector<int> gcdValues(vector<int>& nums, vector<long long>& queries) {
        // Cimpute the frequency table
        int maxNums = nums[0];
        for(int num : nums) maxNums = max(maxNums, num);
        vector<int> freqTable(maxNums + 1);
        for(int num : nums) freqTable[num]++;

        // Table of gcd pairs
        vector<long long> gcdPairs (maxNums + 1);
        for(int num = maxNums; num>=1; --num) {
            long long possibilities = freqTable[num];
            long long overCount = 0;
            for(long long mult=2*num; mult<=maxNums; mult+=num) {
                possibilities += freqTable[mult];
                overCount += gcdPairs[mult];
            }
            long long totalPairs = (possibilities*(possibilities-1))/2;
            totalPairs -= overCount;
            gcdPairs[num] = totalPairs;
        }

        // Turning gcdPairs into a prefixSum
        for(int i=1; i<=maxNums; ++i) {
            gcdPairs[i] += gcdPairs[i-1];
        }

        vector<int> ans(queries.size());
        for(int i=0; i<queries.size(); ++i) {
            long long pos = queries[i];
            auto it = upper_bound(gcdPairs.begin(), gcdPairs.end(), pos);
            ans[i] = it-gcdPairs.begin();
        }
        return ans;
    }
};
