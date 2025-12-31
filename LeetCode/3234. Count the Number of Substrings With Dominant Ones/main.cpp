class Solution {
    int ceilSqrt(int n) {
        int sqrtn = 0;
        for(; (long long)sqrtn*sqrtn < n; sqrtn++);
        return sqrtn;
    }
public:
    // Time: O(n*sqrt(n))
    // Space: O(n), Note that if we use a dequeue instead of a vector, we could use only O(sqrt(n)) space
    int numberOfSubstrings(string s) {
        int n = s.size();
        int sqrtn = ceilSqrt(n);
        vector<int> zeroPos = {n};

        int ans = 0;
        for(int start = n-1; start >= 0; --start) {
            int sumZeros = 0;
            int sumOnes = 0;

            if(s[start]=='1') {
                // Compute the prefix of ones
                sumOnes = zeroPos.back() - start;
                ans += sumOnes;
            }
            else {
                zeroPos.push_back(start);
            }

            int currZero = zeroPos.size() - 1;
            int nextZero = zeroPos.size() - 2;
            while(currZero > 0 && zeroPos.size() - currZero <= sqrtn) {
                sumZeros++;
                // Check if carry is enough to propagate to current string
                if(sumOnes >= sumZeros*sumZeros) {
                    ans += zeroPos[nextZero] - zeroPos[currZero];
                }
                else {
                    int delta = sumZeros*sumZeros - sumOnes;
                    int numStringOnes = zeroPos[nextZero] - zeroPos[currZero] - 1;
                    if(numStringOnes >= delta) {
                        ans += numStringOnes - delta + 1;
                    }
                }
                // Update sumOnes
                sumOnes += zeroPos[nextZero] - zeroPos[currZero] - 1;
                currZero--;
                nextZero--;    
            }
        }
        return ans;
    }
};
