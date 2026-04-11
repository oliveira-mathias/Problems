class Solution {
public:
    // Time: O(RlogR + DlogD)
    // Space: O(R)
    int maxWalls(vector<int>& robots, vector<int>& distance, vector<int>& walls) {
        // We sort the elements in the line
        sort(walls.begin(), walls.end());
        
        vector<int> sortedRobotsIndex;
        for(int i=0; i<robots.size(); ++i) sortedRobotsIndex.push_back(i);
        sort(sortedRobotsIndex.begin(), sortedRobotsIndex.end(),
        [&robots](int l, int r) {
            return robots[l] < robots[r];
        });

        int r = robots.size();
        int DPLeft = 0;
        int DPRight = 0;
        for(int i=r-1; i>=0; --i) {
            int newDPLeft;
            int newDPRight;
            int pos = robots[sortedRobotsIndex[i]];
            int dist = distance[sortedRobotsIndex[i]];

            int lRange = pos - dist;
            if(i>0) {
                lRange = max(robots[sortedRobotsIndex[i-1]]+1, lRange);
            }

            int rRange = pos + dist;
            if(i<r-1) {
                rRange = min(robots[sortedRobotsIndex[i+1]]-1, rRange);
            }

            // DP cases
            // Case shooting left
            auto rIt = upper_bound(walls.begin(), walls.end(), pos);
            auto lEdgeIt = lower_bound(walls.begin(), walls.end(), lRange);

            int rIdx = rIt - walls.begin();
            int lEdgeIdx = lEdgeIt - walls.begin();

            newDPLeft = rIdx-lEdgeIdx;
            if(i < r-1) {
                newDPLeft += max(DPLeft, DPRight);
            }

            // Case shooting right
            rIt = lower_bound(walls.begin(), walls.end(), pos);
            auto rEdgeIt = upper_bound(walls.begin(), walls.end(), rRange);

            rIdx = rIt - walls.begin();
            int rEdgeIdx = rEdgeIt - walls.begin();

            // Case RR
            newDPRight = rEdgeIdx-rIdx;
            if(i<r-1) {
                newDPRight += DPRight;
            }

            // Case RL
            int wallsCount = rEdgeIdx-rIdx;
            if(i<r-1) {
                int neighPos = robots[sortedRobotsIndex[i+1]];
                int neighDist = distance[sortedRobotsIndex[i+1]];

                int neighLRange = neighPos - neighDist;
                neighLRange = max(pos+1, neighLRange);

                auto neighLEdgeIt = lower_bound(walls.begin(), walls.end(), neighLRange);
                int neighlEdgeIdx = neighLEdgeIt - walls.begin();

                if(neighlEdgeIdx<rEdgeIdx) {
                    wallsCount -= rEdgeIdx-neighlEdgeIdx;
                }

                wallsCount += DPLeft;
            }
            newDPRight = max(newDPRight, wallsCount);

            DPLeft = newDPLeft;
            DPRight = newDPRight;
        }

        return max(DPLeft, DPRight);
    }
};
