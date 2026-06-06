class Solution {
public:
    // Time: O(n + m)
    // Space: O(1)
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        auto findEarliestEndTime = [](const vector<int>& firstStart, const vector<int>& firstDuration,
            const vector<int>& secondStart, const vector<int>& secondDuration) -> int
        {
            // Search for earliest first finish time
            int earlistFinishTime = numeric_limits<int>::max();
            for(int i=0; i<firstStart.size(); ++i) {
                earlistFinishTime = min(earlistFinishTime, firstStart[i] + firstDuration[i]);
            }
            // Search for  the earliest possible end time
            int earliestEndTime = numeric_limits<int>::max();
            for(int i=0; i<secondStart.size(); ++i) {
                int start = secondStart[i];
                int duration = secondDuration[i];
                earliestEndTime = min(earliestEndTime, max(earlistFinishTime, start) + duration);
            }
            return earliestEndTime;
        };
        int ans = findEarliestEndTime(landStartTime, landDuration, waterStartTime, waterDuration);
        ans = min(ans, findEarliestEndTime(waterStartTime, waterDuration, landStartTime, landDuration));
        return ans;
    }
};
