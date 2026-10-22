class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    vector<int> targetIndices(const vector<int>& nums, int target) {
        int smallerThanTarget = 0;
        int targetOcc = 0;
        for(int num : nums) {
            if(num < target) {
                smallerThanTarget++;
            }
            else if(num==target) {
                targetOcc++;
            }
        }
        vector<int> ans(targetOcc);
        iota(ans.begin(), ans.end(), smallerThanTarget);
        return ans;
    }
};
