class Solution {
public:
    // Time: O(2^n*log(min{coins[i]}))
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
            // count trailing zeros
            int newCoin = __builtin_ctz(mask);
            unsigned coinMask = 1U << newCoin;

            unsigned subset = mask & ~coinMask;
            long long setLCM = std::lcm(lcm[subset], static_cast<long long>(coins[newCoin]));
            lcm[mask] = (setLCM > k*smallestCoin) ? (k*smallestCoin + 1) : setLCM;
        }

        auto countLessThanX = [&lcm, expN, n](long long X) -> long long {
            long long numElements = 0; 
            for(unsigned mask = 1U; mask < expN; mask++) {
                int setSize = __builtin_popcount(mask);
                long long contribution = X/lcm[mask];
                numElements += (setSize%2) ? contribution : -contribution;
            }
            return numElements;
        };

        long long l = 1;
        long long r = k*smallestCoin + 1;
        while(l < r) {
            long long m = l + (r-l)/2;

            if(countLessThanX(m) >= k) {
                r = m;
            }
            else {
                l = m + 1;
            }
        }

        return l;
        
    }
};
