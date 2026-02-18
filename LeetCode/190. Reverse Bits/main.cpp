class Solution {
public:
    int reverseBits(int n) {
        unsigned upperMask = 1U << 31;
        unsigned lowerMask = 1;
        int res = 0;

        for(; lowerMask < upperMask; lowerMask <<= 1, upperMask >>= 1) {
            if(n & lowerMask) {
                res |= upperMask;
            }

            if(n & upperMask) {
                res |= lowerMask;
            }
        }

        return res;
    }
};
