class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    void moveZeroes(vector<int>& nums) {
        int read = 0;
        int write = 0;
        while(read<nums.size()) {
            if(nums[read]) {
                nums[write] = nums[read];
                read++;
                write++;
            }
            else {
                read++;
            }
        }
        // Fixing the suffix
        if(write < nums.size()) {
            fill(nums.begin() + write, nums.end(), 0);
        }
    }
};
