class Solution {
public:
    // Solution: Linear scan to find the split point of the array
    // Time: O(n)
    // Space: O(1)
    int minimumDeletions(string s) {
        int n = s.size();

        // Compute the prefix sum
        int totalACount = 0;
        for(char c : s) {
            if(c == 'a') {
                totalACount++;
            }
        }

        // Remove all the 'a's
        int minRemovals = totalACount;
        // Consider each position to split the final array
        int aPrefixSum = 0;
        for(int i=0; i<n; ++i) {
            if(s[i] == 'a') {
                aPrefixSum++;
            }
            int splitPrefixBSum = (i+1) - aPrefixSum;
            int splitSuffixASum = totalACount - aPrefixSum;
            minRemovals = min(minRemovals, splitPrefixBSum + splitSuffixASum);
        }

        return minRemovals;
    }
};
