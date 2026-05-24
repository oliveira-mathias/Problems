class Solution {
public:
    // Time: O(log(n))
    // Space: O(1)
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        while(l < r) {
            int m = l + (r-l)/2;

            if(nums[m] > nums[r]) {
                // The subarray [l, m] must be sorted
                if(target >= nums[l] && target <= nums[m]) {
                    r = m;
                }
                else {
                    l = m+1;
                }
            }
            // All elements are distinct
            else {
                // The subarray [m, r] must be sorted
                if(target >= nums[m] && target <= nums[r]) {
                    if(nums[m]==target) return m;
                    l = m+1;
                }
                else {
                    r = m;
                }
            }
        }

        return nums[l]==target ? l : -1;
    }
};
