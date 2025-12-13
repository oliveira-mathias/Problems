class Solution {
public:
    long long maximumTotalDamage(vector<int>& power) {
        // Sort the array in increasing order
        sort(power.begin(), power.end());

        int n = power.size();
        vector<long long> suffixMaxDP(n);
        vector<long long> DP(n);

        // Base case
        suffixMaxDP[n-1] = power[n-1];
        DP[n-1] = power[n-1];

        // Recursive step
        for(int i=n-2; i>=0; --i) {
            if(power[i] == power[i+1]) {
                DP[i] = power[i] + DP[i+1];
            }
            else {
                auto startSearchPos = lower_bound(power.begin(), power.end(), power[i] + 3);
                if(startSearchPos==power.end()) {
                    DP[i] = power[i];
                }
                else {
                    int startSearchPosIndex = startSearchPos - power.begin();
                    DP[i] = power[i] + suffixMaxDP[startSearchPosIndex];
                }
            }
            suffixMaxDP[i] = max(DP[i], suffixMaxDP[i+1]);
        }

        return suffixMaxDP[0];
    }
};
