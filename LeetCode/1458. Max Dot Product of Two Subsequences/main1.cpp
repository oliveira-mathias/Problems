class Solution {
public:
    // Time: O(m*n)
    // Space: O(m)
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        // The remaining cases we solve using the DP
        int n = nums1.size();
        int m = nums2.size();

        vector<long long> currRow(m + 1, numeric_limits<long long>::lowest());
        vector<long long> nextRow(m + 1, numeric_limits<long long>::lowest());

        for(int i=n-1; i>=0; --i) {
            for(int j=m-1; j>=0; --j) {
                // Note that by initializinf the DP differently and using max(0, nextRow[j+1]), we allow the DP
                // to start a new subsequence and ensure that a non-empty subsequence will be selected
                long long DPij = nums1[i] * nums2[j] + max(0LL, nextRow[j+1]);
                DPij = max(DPij, nextRow[j]);
                DPij = max(DPij, currRow[j+1]);

                currRow[j] = DPij;
            }
            swap(currRow, nextRow);
        }

        return nextRow[0];
    }
};
