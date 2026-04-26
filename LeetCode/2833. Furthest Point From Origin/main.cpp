class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int furthestDistanceFromOrigin(string moves) {
        int freeSteps = 0;
        int balance = 0;
        for(char move : moves) {
            switch(move) {
                case 'L': balance--; break;
                case 'R': balance++; break;
                default: freeSteps++;
            }
        }

        return abs(balance) + freeSteps;
    }
};
