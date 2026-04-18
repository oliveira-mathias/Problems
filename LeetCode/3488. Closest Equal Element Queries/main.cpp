class Solution {
public:
    // Time: O(n + q)
    // Space: O(n)
    vector<int> solveQueries(vector<int>& nums, vector<int>& queries) {
        int n = nums.size();
        
        unordered_map<int, int> firstSeen;
        unordered_map<int, int> lastSeen;

        vector<int> shortestDist (n, numeric_limits<int>::max());

        for(int i=0; i<n; ++i) {
            if(!firstSeen.contains(nums[i])) {
                firstSeen[nums[i]] = i;
                lastSeen[nums[i]] = i;
            }
            else {
                // Here we compute its edges distances
                int j = lastSeen[nums[i]];
                int distFromPrev = i - j;

                shortestDist[i] = min(shortestDist[i], distFromPrev);
                shortestDist[j] = min(shortestDist[j], distFromPrev);

                lastSeen[nums[i]] = i;

                // Now we consider the circular edge
                int first = firstSeen[nums[i]];
                int distFromFirst = (n-i) + first;

                shortestDist[i] = min(shortestDist[i], distFromFirst);
                shortestDist[first] = min(shortestDist[first], distFromFirst);
            }
        }

        vector<int> queriesResult;
        queriesResult.reserve(queries.size());
        for(int query : queries) {
            int minDist = (shortestDist[query] > n) ? -1 : shortestDist[query];
            queriesResult.push_back(minDist);
        }

        return queriesResult;
    }
};
