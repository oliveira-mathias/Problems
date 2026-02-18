class Solution {
public:
    bool hasAlternatingBits(int n) {
        unsigned shiftedMask = (n >> 1);
        unsigned xorResult = n ^ shiftedMask;
        return (__builtin_popcount(xorResult + 1) == 1);
    }
};
