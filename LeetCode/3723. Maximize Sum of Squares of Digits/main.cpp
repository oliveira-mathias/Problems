class Solution {
public:
    // Time: O(num)
    // Space: O(1)
    string maxSumOfSquares(int num, int sum) {
        constexpr int MAX_DIGIT = 9;
        // Checking whether there exists a solution
        if(MAX_DIGIT*num < sum) return ""; 

        string ans(num, '0');
        for (int i=0; i<num && sum; ++i) {
            int digit = min(MAX_DIGIT, sum);
            ans[i] = digit + '0';
            sum -= digit;
        }
        return ans;
    }
};
