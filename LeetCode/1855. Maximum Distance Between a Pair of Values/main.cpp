class Solution {
public:
    // Time: O(n + m)
    // Space: O(1)
    int maxDistance(vector<int>& nums1, vector<int>& nums2) {
        int i = 0, j = 0;

        int maxDist = 0;
        while(i < nums1.size() && j < nums2.size()) {
            // We look for the fathest j such that nums2[j] > nums1[i]
            while(j < nums2.size() && nums2[j] >= nums1[i]) {
                ++j;
            }

            // If no such number exists the distance will be -1
            maxDist = max(maxDist, j - i -1);

            // Updating the indexes
            ++i;
            if(i > j) {
                ++j;
            }
        }

        return maxDist;
    }
};
