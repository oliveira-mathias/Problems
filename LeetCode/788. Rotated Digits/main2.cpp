class Solution {
public:
    // Time: O(log(n))
    // Space: O(log(n))
    int rotatedDigits(int n) {
        vector<int> digits;

        while(n) {
            int digit = n % 10;
            n /= 10;
            digits.push_back(digit);
        }
        digits.push_back(0);

        int m = digits.size();
        vector<vector<int>> DP(m, vector<int>(4, -1));

        auto solve = [&DP, &digits](this auto&& solve, int index, int isGood, int isTight) -> int {
            // Base step
            // We are not traversing paths that contains invalid digits
            if(index == 0) return isGood;

            // Recursive step
            int secondIndex = 2*isGood + isTight;
            if(DP[index][secondIndex] != -1) return DP[index][secondIndex];

            int ans = 0;
            int limit = (isTight) ? digits[index-1] : 9;

            for(int digit=0; digit<=limit; ++digit) {
                // Invalid digits
                if(digit == 3 || digit ==4 || digit == 7) continue;

                // Symetrical digits
                if(digit==0 || digit==1 || digit==8) ans += solve(index-1, isGood, (isTight && digit==limit) ? 1 : 0);
                
                // Asymetrical digits
                else if(digit==2 || digit==5 || digit==6 || digit==9) ans += solve(index-1, 1, (isTight && digit==limit) ? 1 : 0);
            }

            return DP[index][secondIndex] = ans;
        };

        return solve(m-1, 0, 1);
        
    }
};
