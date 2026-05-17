class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int rotatedDigits(int n) {
        auto isValidGoodNumber = [](int num) -> bool {
            int nonSimetricalCount = 0;
            
            while(num != 0) {
                int digit = num % 10;
                num /= 10;
                
                switch(digit) {
                    case 3:
                    case 4:
                    case 7:
                        return false;
                    case 2:
                    case 5:
                    case 6:
                    case 9:
                        nonSimetricalCount++;
                }
            }

            return (nonSimetricalCount > 0);
        };

        int ans = 0;
        for(int i=1; i<=n; ++i) {
            if(isValidGoodNumber(i)) ++ans;
        }

        return ans;
    }
};
