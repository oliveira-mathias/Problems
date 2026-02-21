class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        unordered_set<int> primes = {2,3,5,7,11,13,17,19,23,29};
        
        auto countNumberOfSetBits = [&primes](unsigned n) -> int {
            int sum = 0;
            for(unsigned mask = 1U; mask != 0U; mask <<= 1) {
                if(mask & n) {
                    sum++;
                }
            }
            return sum;
        };

        int numbersWithPrimeBitsSet = 0;
        for(int n = left; n <= right; ++n) {
            if(primes.contains(countNumberOfSetBits(n))) {
                numbersWithPrimeBitsSet++;
            }
        }

        return numbersWithPrimeBitsSet;
    }
};
