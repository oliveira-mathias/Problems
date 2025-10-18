class Solution {
    int findKMergedElement(vector<int>& nums1, vector<int>& nums2, int k) {
        int l, m, r;

        // First search for this element in the nums2 array
        l=0;
        r=nums2.size();

        while(l<r) {
            m = l + (r-l)/2;

            auto it = upper_bound(nums1.begin(), nums1.end(), nums2[m]);

            // Count the position of this element in the sorted array
            int pos = m + (it-nums1.begin());
            if(pos == k) {
                return nums2[m];
            }
            else if(pos < k) {
                l = m + 1;
            }
            else {
                r = m;
            }
        }

        // Then we search for this element in the nums1 array
        l=0;
        r = nums1.size();

        while(l<r) {
            m = l + (r-l)/2;

            auto it = lower_bound(nums2.begin(), nums2.end(), nums1[m]);

            // Count the position of this element in the array
            int pos = m + (it-nums2.begin());
            if(pos == k) {
                return nums1[m];
            }
            else if(pos < k) {
                l = m + 1;
            }
            else {
                r = m;
            }
        }

        // Invalid return value
        return -10000000;
    }
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();
        int m = nums2.size();

        if((n+m)%2==0) {
            double val1 = findKMergedElement(nums1, nums2, (m+n)/2);
            double val2 = findKMergedElement(nums1, nums2, ((m+n)/2 - 1));

            return (val1+val2)/2;
        }
        else {
            return findKMergedElement(nums1, nums2, (m+n)/2);
        }
    }
};
