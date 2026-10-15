class Solution {
public:
    // Time: O(n²)
    // Space: O(1)
    int sumCounts(const vector<int>& nums) {
        int ans = 0;
        constexpr int MAX_VAL = 100;
        vector<bool> contains(MAX_VAL+1);
        for(int i=0; i<nums.size(); ++i) {
            int uniques = 0;
            for(int j=i; j<nums.size(); ++j) {
                if(!contains[nums[j]]) {
                    contains[nums[j]] = true;
                    uniques++;
                }
                ans += uniques*uniques;
            }
            fill(contains.begin(), contains.end(), false);
        }
        return ans;
    }
};
