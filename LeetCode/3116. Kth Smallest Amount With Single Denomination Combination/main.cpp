class Solution {
public:
    // Time: O(2^n*log(coins[i]))
    // Space: O(2^n)
    long long findKthSmallest(vector<int>& coins, int k) {
        int n = coins.size();
        int expN = 1U << n;

        // Searching fo the smallesCoin
        long long smallestCoin = numeric_limits<int>::max();
        for(long long coin : coins) {
            smallestCoin = min(coin, smallestCoin);
        }

        vector<long long> lcm(expN);
        lcm[0] = 1;
        for(unsigned mask = 1U; mask<expN; ++mask) {
            // Searching for a coin to insert
            int newCoin = 0;
            unsigned coinMask = 1U;
            // Probably could use some compiler built in function
            for(; coinMask <expN; coinMask <<= 1, newCoin++) {
                if(coinMask & mask) break;
            }

            unsigned subset = mask & ~coinMask;
            long long setLCM = std::lcm(lcm[subset], static_cast<long long>(coins[newCoin]));
            lcm[mask] = (setLCM > k*smallestCoin) ? (k*smallestCoin + 1) : setLCM;
        }

        vector<long long> incExc (n+1);
        auto countLessThanX = [&incExc, &lcm, expN, n](long long X) -> long long {
            fill(incExc.begin(), incExc.end(), 0);
            for(unsigned mask = 1U; mask < expN; mask++) {
                int setSize = __builtin_popcount(mask);
                incExc[setSize] += X/lcm[mask];
            }
            long long numElements = 0; 
            for(int i=1; i<=n; ++i) {
                numElements = incExc[i] - numElements;
            }
            return numElements > 0 ? numElements : -numElements;
        };

        long long l = 1;
        long long r = k*smallestCoin + 1;
        long long ans = 0;
        while(l < r) {
            long long m = l + (r-l)/2;

            if(countLessThanX(m) > k) {
                r = m;
            }
            else {
                l = m + 1;
                ans = m;
            }
        }

        // Search for the closest element in the sequence
        bool foundMultiple = false;
        while(!foundMultiple) {
            for(int i=0; i<n; ++i) {
                if(ans % coins[i] == 0) {
                    foundMultiple = true;
                    break;
                }
            }
            if(!foundMultiple) {
                ans--;
            }
        }

        return ans;
        
    }
};
