class Solution {
public:
    // Time: O(n log(n))
    // Space: O(log(n))
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        // Sort the intervals
        sort(intervals.begin(), intervals.end());

        const auto doIntercept = [](const vector<int>& iLeft, const vector<int>& iRight) -> bool {
            return iRight[0] <= iLeft[1];
        };

        vector<vector<int>> ans;
        for(int i=0; i<intervals.size();) {
            vector<int> merged = intervals[i];
            ++i;
            for(; i<intervals.size() && doIntercept(merged, intervals[i]); ++i) {
                merged[1] = max(merged[1], intervals[i][1]);
            }
            ans.push_back(merged);
        }
        return ans;
    }
};
