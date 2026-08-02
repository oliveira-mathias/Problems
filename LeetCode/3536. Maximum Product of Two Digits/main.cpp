class Solution {
public:
    int maxProduct(int n) {
        int d1 = -1;
        int d2 = -1;
        
        while(n) {
            int digit = n%10;

            if(digit > d1) {
                // d2 d1 -> d1 digit
                d2 = d1;
                d1 = digit;
            }
            else if(digit > d2) {
                // d2 d1 -> digit d1
                d2 = digit;
            }

            n /= 10;
        }
        return d1*d2;
    }
};
