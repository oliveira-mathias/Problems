class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    bool isGood(vector<int>& nums) {
        int n = nums.size()-1;
        for(int i=0; i<n; ++i) {
            while(nums[i] != i+1) {
                if(nums[i] > n || nums[i] < 1) return false;
                
                int index = nums[i]-1;
                if(nums[i] == n && nums[index] == n) ++index;

                if(nums[index] == nums[i]) return false;
                swap(nums[index], nums[i]); 
            }
        }

        return nums[n] == n;
    }
};
