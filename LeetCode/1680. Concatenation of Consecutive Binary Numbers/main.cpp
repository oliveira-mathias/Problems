class Solution {
public:
    int concatenatedBinary(int n) {
        auto numberOfBits = [](unsigned number) -> unsigned {
            unsigned bits = 32;
            unsigned mask = 1U << 31;

            while(!(mask & number)) {
                bits--;
                mask >>= 1;
            }
            return bits;
        };

        constexpr unsigned long long MOD = 1000000007;
        unsigned long long offset = 1;
        unsigned res = 0;
        for(unsigned number = n; number > 0; --number) {
            unsigned long long sumElement = number * offset;
            sumElement += res;
            res = sumElement % MOD;

            // Updating variables for next iteration
            offset <<= numberOfBits(number);
            if(offset > MOD) {
                offset %= MOD;
            }
        }
        return res;
    }
};
