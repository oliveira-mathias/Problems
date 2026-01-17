class Solution {
public:
    // Time: O(m*n)
    // Space: O(m)
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        // Handling the case in which the DP solution is the empty sequence
        auto isAllPositive = [](vector<int>& v) -> bool {
            for(int num : v) {
                if(num <= 0) {
                    return false;
                }
            }
            return true;
        };

        auto isAllNegative = [](vector<int>& v) -> bool {
            for(int num : v) {
                if(num >= 0) {
                    return false;
                }
            }
            return true;
        };

        if((isAllPositive(nums1) && isAllNegative(nums2))
            || (isAllPositive(nums2) && isAllNegative(nums1))) {
            
            auto getSmallerAbsElement = [](vector<int>& v) {
                int smaller = v[0];
                for(int num : v) {
                    if(abs(smaller) > abs(num)) {
                        smaller = num;
                    }
                }
                return smaller;
            };

            return getSmallerAbsElement(nums1)*getSmallerAbsElement(nums2);
        }

        // The remaining cases we solve using the DP
        int n = nums1.size();
        int m = nums2.size();

        vector<long long> currRow(m + 1, 0);
        vector<long long> nextRow(m + 1, 0);

        for(int i=n-1; i>=0; --i) {
            for(int j=m-1; j>=0; --j) {
                long long DPij = nums1[i] * nums2[j] + nextRow[j+1];
                DPij = max(DPij, nextRow[j]);
                DPij = max(DPij, currRow[j+1]);

                currRow[j] = DPij;
            }
            swap(currRow, nextRow);
        }

        return nextRow[0];
    }
};
