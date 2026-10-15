class Solution {
public:
    // Time: O(n²)
    // Space: O(1)
    int sumCounts(const vector<int>& nums) {
        int ans = 0;
        unordered_set<int> elems;
        for(int i=0; i<nums.size(); ++i) {
            for(int j=i; j<nums.size(); ++j) {
                elems.insert(nums[j]);
                int uniques = elems.size();
                ans += uniques*uniques;
            }
            elems.clear();
        }
        return ans;
    }
};
