class Solution {
public:
    int search(vector<int>& nums, int target) {
        int l = 0;
        int r = nums.size() - 1;

        // We first search fo the smallest element
        while(l < r) {
            int m = l + (r-l)/2;
            if(nums[m] > nums[r]) {
                l = m + 1;
            }
            // All elements are distinct
            else {
                r = m;
            }
        }

        // Then we know the array is increasing in [0, l-1] [l, nums.size()-1]
        // The subarray [0, l) can be empty
        if(target >= nums[0] && l>0 && target <= nums[l-1]) {
            auto it = lower_bound(nums.begin(), nums.begin() + l, target);
            int index = it - nums.begin();
            return (index < l && nums[index]==target) ? index : -1;
        }
        else if(target >= nums[l] && target <= nums.back()) {
            auto it = lower_bound(nums.begin() + l, nums.end(), target);
            int index = it - nums.begin();
            return (index < nums.size() && nums[index]==target) ? index : -1;
        }
        return -1;
    }
};
