class Solution {
public:
    // Time: O(log(n))
    // Space: O(1)
    bool checkDivisibility(int n) {
        int digitsSum = 0;
        int digitsProduct = 1;
        for(int num = n; num>0; num /=10) {
            int digit = num % 10;
            digitsSum += digit;
            digitsProduct *= digit;
        }
        return n % (digitsSum + digitsProduct) == 0;
    }
};
