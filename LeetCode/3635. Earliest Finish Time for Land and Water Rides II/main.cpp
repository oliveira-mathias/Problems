class Solution {
public:
    // Time: O(n log(n) + m log(m))
    // Space: O(n + m)
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        vector<pair<int, int>> land;
        land.reserve(n);
        vector<pair<int, int>> water;
        water.reserve(m);

        // Ordering events
        for(int i=0; i<n; ++i) {
            int start = landStartTime[i];
            int duration = landDuration[i];
            land.emplace_back(start, duration);
        }
        for(int j=0; j<m; ++j) {
            int start = waterStartTime[j];
            int duration = waterDuration[j];
            water.emplace_back(start, duration);
        }
        sort(land.begin(), land.end());
        sort(water.begin(), water.end());

        // If land is the first
        auto minAccomplishTime = [](const vector<pair<int, int>>& first, const vector<pair<int, int>>& second) {
            int n = second.size();
            vector<int> prefixMin(n);
            vector<int> suffixMin(n);

            // Initializing arrays
            prefixMin[0] = second[0].second;
            for(int i=1; i<n; ++i) {
                prefixMin[i] = min(prefixMin[i-1], second[i].second);
            }
            suffixMin[n-1] = second[n-1].first + second[n-1].second;
            for(int i=n-2; i>=0; --i) {
                suffixMin[i] = min(suffixMin[i+1], second[i].first + second[i].second);
            }

            // Computing the earliest end time
            int earliestEndTime = numeric_limits<int>::max();
            for(int j=0; j<first.size(); ++j) {
                int end = first[j].first + first[j].second;
                auto secIt = lower_bound(second.begin(), second.end(), make_pair(end, 0));
                int i = secIt-second.begin();

                int minEndTime;
                if(i == second.size()) {
                    minEndTime = end + prefixMin.back();
                }
                else if(i == 0) {
                    minEndTime = suffixMin.front();
                }
                else {
                    minEndTime = min(end + prefixMin[i-1], suffixMin[i]);
                }
                earliestEndTime = min(earliestEndTime, minEndTime);
            }
            return earliestEndTime;
        };
        int ans = minAccomplishTime(land, water);
        ans = min(ans, minAccomplishTime(water, land));
        return ans;
    }
};
