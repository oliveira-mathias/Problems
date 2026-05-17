class Solution {
public:
    int findMin(vector<int>& nums) {
        int l = 0;
        int r = nums.size();
        int minElem = nums[0];
        
        while(l < r) {
            int mid = l + (r-l)/2;

            if(nums[mid] < nums[l]) {
                minElem = min(nums[mid], minElem);
                r = mid;
            }
            else if(nums[mid] > nums[l]) {
                minElem = min(nums[l], minElem);
                l = mid + 1;
            }
            else {
                minElem = min(nums[l], minElem);
                ++l;
            }
        }

        return minElem;
    }
};
