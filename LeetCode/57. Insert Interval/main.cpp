class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        int n = intervals.size();
        const auto doIntersect = [](const vector<int>& i1, const vector<int>& i2) -> bool {
            int start1 = i1[0];
            int end1 = i1[1];
            int start2 = i2[0];
            int end2 = i2[1];

            return ((start1 >= start2) && (start1 <= end2)) || ((start2 >= start1) && (start2 <= end1));
        };

        int i = 0;
        vector<vector<int>> ans;
        for(; i<n && !doIntersect(intervals[i], newInterval) && newInterval[0] > intervals[i][0]; ++i) {
            ans.push_back(intervals[i]);
        }

        int mergedStart = newInterval[0];
        int mergedEnd = newInterval[1];
        for(;i<n && doIntersect(intervals[i], newInterval); ++i) {
            mergedStart = min(mergedStart, intervals[i][0]);
            mergedEnd = max(mergedEnd, intervals[i][1]);
        }
        ans.push_back({mergedStart, mergedEnd});

        for(; i<n; ++i) {
            ans.push_back(intervals[i]);
        }

        return ans;
    }
};
