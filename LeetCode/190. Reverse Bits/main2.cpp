class Solution {
public:
    int reverseBits(int n) {
        unsigned mask = n;

        mask = ((mask & 0x0000ffff) << 16) | ((mask & 0xffff0000) >> 16);
        mask = ((mask & 0x00ff00ff) << 8) | ((mask & 0xff00ff00) >> 8);
        mask = ((mask & 0x0f0f0f0f) << 4) | ((mask & 0xf0f0f0f0) >> 4);
        mask = ((mask & 0x33333333) << 2) | ((mask & 0xcccccccc) >> 2);
        mask = ((mask & 0x55555555) << 1) | ((mask & 0xaaaaaaaa) >> 1);

        return mask;
    }
};
