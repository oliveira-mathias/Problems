class Solution {
public:
    int minimumCost(vector<int>& nums) {
        int minimum = min(nums[1], nums[2]);
        int secondMinimum = max(nums[1], nums[2]);

        for(int i=3; i<nums.size(); ++i) {
            if(nums[i] < minimum) {
                secondMinimum = minimum;
                minimum = nums[i];
            }
            else if(nums[i] < secondMinimum) {
                secondMinimum = nums[i];
            }
        }

        return nums[0] + minimum + secondMinimum;
    }
};
