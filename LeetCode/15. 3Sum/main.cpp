class Solution {
public:
    // Time: O(n²)
    // Space: O(n²) - Considering the output size
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;

        for(int i=0; i<nums.size(); ++i) {
            if(i>0 && nums[i]==nums[i-1]) {
                continue;
            }
            int target = -nums[i];
            int l=i+1, r=nums.size()-1;
            while(l<r) {
                // Now we check for the sum
                if(nums[l] + nums[r] == target) {
                    ans.push_back({nums[i], nums[l], nums[r]});
                    int currLValue = nums[l];
                    while(l<r && nums[l]==currLValue) {
                        ++l;
                    }
                }
                else if(nums[l] + nums[r] > target) {
                    --r;
                }
                else {
                    ++l;
                }
            }
        }
        return ans;
    }
};
