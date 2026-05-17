class Solution {
public:
    int findMin(vector<int>& nums) {
        int minNum = nums[0];
        int l = 0;
        int r = nums.size();
        
        while(l < r) {
            int mid = l + (r-l)/2;

            if(nums[l] < nums[r-1]) {
                minNum = min(nums[l], minNum);
                break;
            }
            else if(nums[l] > nums[r-1]) {
                if(nums[mid] <= nums[r-1]) {
                    minNum = min(minNum, nums[mid]);
                    r = mid;
                }
                else if(nums[mid] > nums[r-1]) {
                    minNum = min(minNum, nums[mid]);
                    l = mid + 1;
                }
            }
            else {
                if(nums[mid] > nums[r-1]) {
                    minNum = min(minNum, nums[r-1]);
                    l = mid + 1;
                }
                else if(nums[mid] < nums[r-1]) {
                    minNum = min(minNum, nums[mid]);
                    r = mid;
                }
                else{
                    minNum = min(minNum, nums[mid]);
                    ++l;
                    --r;   
                }
            }
        }

        return minNum;
    }
};
