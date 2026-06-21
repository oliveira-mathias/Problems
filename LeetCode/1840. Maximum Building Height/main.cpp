class Solution {
public:
    // Time: O(m log(m))
    // Space: O(m)
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        restrictions.push_back({1, 0});
        // Sort restrictions
        sort(restrictions.begin(), restrictions.end(), 
        [](const vector<int>& a, const vector<int>& b) {
            return a[0] < b[0];
        });

        int m = restrictions.size();
        vector<int> maxHeights(m, 0);

        // Prefix heights
        for(int i=1; i<m; ++i) {
            int prevPos = restrictions[i-1][0];
            int currPos = restrictions[i][0];
            int currLimit = restrictions[i][1];
            int increaseSlots = currPos - prevPos;
            maxHeights[i] = min(maxHeights[i-1] + increaseSlots, currLimit);
        }
        // Suffix heights
        for(int i=m-2; i>=0; --i) {
            int nextPos = restrictions[i+1][0];
            int currPos = restrictions[i][0];
            int increaseSlots = nextPos - currPos;
            maxHeights[i] = min(maxHeights[i+1] + increaseSlots, maxHeights[i]);
        }

        int maxHeight = maxHeights[0];
        for(int i=1; i<m; ++i) {
            int prevPos = restrictions[i-1][0];
            int currPos = restrictions[i][0];
            int gapSlots = currPos - prevPos - 1;

            // Remove the slots needed to equal maxHeight
            int maxBoundarySize = max(maxHeights[i-1], maxHeights[i]);
            int minBoundarySize = min(maxHeights[i-1], maxHeights[i]);
            gapSlots -= maxBoundarySize - minBoundarySize;

            if(gapSlots & 1U) gapSlots++;
            maxHeight = max(maxHeight, maxBoundarySize + gapSlots/2);
        }
        // There is possibly one last slot
        if(restrictions.back()[0] < n) {
            int lastPos = restrictions.back()[0];
            int gapSlots = n - lastPos;
            maxHeight = max(maxHeight, maxHeights.back() + gapSlots);
        }
        return maxHeight;
    }
};
