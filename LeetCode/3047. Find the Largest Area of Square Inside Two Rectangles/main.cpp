class Solution {
    bool isSorted(int a, int b, int c) {
        return (a <= b) && (b <= c);
    }
    long long computeMaxSquareInstersectingArea(vector<int>& bottom1, vector<int>& top1, vector<int>& bottom2, vector<int>& top2) {
        if(isSorted(bottom1[0], bottom2[0], top1[0])) {
            if(isSorted(bottom1[1], bottom2[1], top1[1])) {
                int intersectingWidth = min(top2[0], top1[0]) - bottom2[0];
                int intersectingHeight = min(top2[1], top1[1]) - bottom2[1];
                long long squareSide = min(intersectingWidth, intersectingHeight);
                return squareSide*squareSide;
            }
            else if(isSorted(bottom2[1], bottom1[1], top2[1])) {
                int intersectingWidth = min(top2[0], top1[0]) - bottom2[0];
                int intersectingHeight = min(top2[1], top1[1]) - bottom1[1];
                long long squareSide = min(intersectingWidth, intersectingHeight);
                return squareSide*squareSide;
            }
            else {
                // They do not intersect
                return 0;
            }
        }
        else if(isSorted(bottom2[0], bottom1[0], top2[0])) {
            if(isSorted(bottom1[1], bottom2[1], top1[1])) {
                int intersectingWidth = min(top1[0], top2[0]) - bottom1[0];
                int intersectingHeight = min(top1[1], top2[1]) - bottom2[1];
                long long squareSide = min(intersectingWidth, intersectingHeight);
                return squareSide*squareSide;
            }
            else if(isSorted(bottom2[1], bottom1[1], top2[1])) {
                int intersectingWidth = min(top1[0], top2[0]) - bottom1[0];
                int intersectingHeight = min(top1[1], top2[1]) - bottom1[1];
                long long squareSide = min(intersectingWidth, intersectingHeight);
                return squareSide*squareSide;
            }
            else {
                // They do not intersect
                return 0;
            }
        }
        else {
            // They do not intersect
            return 0;
        }
    }
public:
    long long largestSquareArea(vector<vector<int>>& bottomLeft, vector<vector<int>>& topRight) {
        long long maxArea = 0;
        int n = bottomLeft.size();
        for(int i=0; i<n; ++i) {
            for(int j=i+1; j<n; ++j) {
                maxArea = max(maxArea, computeMaxSquareInstersectingArea(bottomLeft[i], topRight[i], bottomLeft[j], topRight[j]));
            }
        }

        return maxArea;
    }
};
