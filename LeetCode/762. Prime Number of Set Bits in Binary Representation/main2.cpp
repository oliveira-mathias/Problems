class Solution {
public:
    int countPrimeSetBits(int left, int right) {
        constexpr int primesMask = 0b00100000100010100010100010101100;
        
        int numbersWithPrimeBitsSet = 0;
        for(int n = left; n <= right; ++n) {
            if((1U << popcount((unsigned)n)) & primesMask) {
                numbersWithPrimeBitsSet++;
            }
        }

        return numbersWithPrimeBitsSet;
    }
};
