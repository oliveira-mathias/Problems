class Solution {
public:
    vector<int> constructTransformedArray(vector<int>& nums) {
        int n = nums.size();
        
        vector<int> res;
        res.reserve(n);
        
        for(int i=0; i<n; ++i) {
            int index = (i + nums[i])%n;
            
            if(index < 0) index += n;
            
            res.push_back(nums[index]);
        }
        return res;
    }
};
