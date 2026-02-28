class Solution {
public:
    int maxGoodNumber(vector<int>& nums) {
        int res = 0;
        int op = 0;
        
        // Option 0 1 2
        op = ((((nums[0]) << std::bit_width((unsigned)nums[1])) | nums[1]) << std::bit_width((unsigned)nums[2])) | nums[2];
        if(op > res) res = op;
        
        // Option 0 2 1
        op = ((((nums[0]) << std::bit_width((unsigned)nums[2])) | nums[2]) << std::bit_width((unsigned)nums[1])) | nums[1];
        if(op > res) res = op;

        // Option 1 0 2
        op = ((((nums[1]) << std::bit_width((unsigned)nums[0])) | nums[0]) << std::bit_width((unsigned)nums[2])) | nums[2];
        if(op > res) res = op;

        // Option 1 2 0
        op = ((((nums[1]) << std::bit_width((unsigned)nums[2])) | nums[2]) << std::bit_width((unsigned)nums[0])) | nums[0];
        if(op > res) res = op;

        // Option 2 0 1
        op = ((((nums[2]) << std::bit_width((unsigned)nums[0])) | nums[0]) << std::bit_width((unsigned)nums[1])) | nums[1];
        if(op > res) res = op;

        // Option 2 1 0
        op = ((((nums[2]) << std::bit_width((unsigned)nums[1])) | nums[1]) << std::bit_width((unsigned)nums[0])) | nums[0];
        if(op > res) res = op;

        return res;
    }
};
