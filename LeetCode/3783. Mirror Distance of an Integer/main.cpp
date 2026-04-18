class Solution {
public:
    // Time: O(log(n))
    // Space: O(1)
    int mirrorDistance(int n) {
        int mirrored = 0;
        int number = n;
        while(number != 0) {
            int digit = number % 10;
            number /= 10;

            mirrored = 10*mirrored + digit;
        }

        return abs(n - mirrored);
    }
};
