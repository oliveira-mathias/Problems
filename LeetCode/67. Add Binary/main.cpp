class Solution {
public:
    string addBinary(string a, string b) {
        string sum;
        int carry = 0;

        for(int i=a.size()-1, j=b.size()-1; i>=0 || j>=0 || carry; --i, --j) {
            if(i >= 0) {
                carry += a[i]-'0';
            }

            if(j >= 0) {
                carry += b[j]-'0';
            }

            sum += (carry & 1) + '0';
            carry >>= 1;
        }

        reverse(sum.begin(), sum.end());

        return sum;
    }
};
