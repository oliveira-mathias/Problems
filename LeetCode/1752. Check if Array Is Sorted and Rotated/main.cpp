class Solution {
public:
    bool check(vector<int>& nums) {
        int inversions = 0;
        for(int i=1; i<nums.size(); ++i) {
            if(nums[i-1] > nums[i]) inversions++;
        }
        if(!inversions) return true;
        if(inversions==1 && nums[0] >= nums.back()) return true;
        return false;
    }
};
