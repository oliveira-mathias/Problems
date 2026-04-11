class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    vector<int> plusOne(vector<int>& digits) {
        reverse(digits.begin(), digits.end());
        
        int carry = 1;
        for(int i=0; i<digits.size(); ++i) {
            digits[i] += carry;
            carry = digits[i]/10;
            digits[i] %= 10;
        }

        if(carry) {
            digits.push_back(carry);
        }

        reverse(digits.begin(), digits.end());
        return digits;
    }
};
