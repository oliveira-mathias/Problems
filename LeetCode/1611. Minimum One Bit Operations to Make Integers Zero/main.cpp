class Solution {
public:
    int minimumOneBitOperations(int n) {
        int rank = 0;
        bool flipState = false;

        for(int mask = (1<<30); mask != 0; mask >>= 1) {
            if(n & mask) {
                if(!flipState) {
                    rank += mask;
                }
                // Bit one flips the state for next iteration
                flipState = !flipState;
            }
            // Bit zero preserves the state for the next iteration
            else if(flipState) {
                rank += mask;
            }
        }

        return rank;
    }
};
