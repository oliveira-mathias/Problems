class Solution {
public:
    // Time: Space: O(nlog(n) + mlog(m))
    // Space: O(log(n) + log(m))
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        sort(vBars.begin(), vBars.end());
        sort(hBars.begin(), hBars.end());

        auto maxConsecutiveSeq = [](vector<int>& v) -> int {
            int maxSeq = 0;
            for(int i=0; i<v.size();) {
                int expected = v[i];
                int currSeq = 0;
                while(i < v.size() && v[i]==expected) {
                    currSeq++;
                    expected++;
                    i++;
                }
                maxSeq = max(maxSeq, currSeq);
            }
            return maxSeq;
        };

        int maxWidth = maxConsecutiveSeq(vBars) + 1;
        int maxHeight = maxConsecutiveSeq(hBars) + 1;
        int squareSide = min(maxWidth, maxHeight);

        return squareSide*squareSide;
    }
};
