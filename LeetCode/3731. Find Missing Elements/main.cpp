class Solution {
public:
    // Time: O((max{nums[i]}-min{nums[i]}) + n log(n))
    // Space: O(log(n))
    vector<int> findMissingElements(vector<int>& nums) {
        vector<int> missing;
        sort(nums.begin(), nums.end());

        int currNumber = nums[0];
        for(int i=0; i<nums.size();) {
            if(nums[i]==currNumber) {
                currNumber++;
                ++i;
            }
            else {
                while(currNumber < nums[i]) {
                    missing.push_back(currNumber);
                    currNumber++;
                }
            }
        }

        return missing;
    }
};
