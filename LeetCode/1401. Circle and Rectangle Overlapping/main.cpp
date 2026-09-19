class Solution {
public:
    // Time: O(1)
    // Space: O(1)
    bool checkOverlap(int radius, int xCenter, int yCenter, int x1, int y1, int x2, int y2) {
        // Translating points
        x1 -= xCenter;
        x2 -= xCenter;
        y1 -= yCenter;
        y2 -= yCenter;

        const auto isPointInsideRectangle = [](int x1, int y1, int x2, int y2, int a, int b) -> bool {
            return ((a>=x1) && (a<=x2)) && ((b>=y1) && (b<=y2));
        };

        const auto isPointInsideOriginCenteredCircle = [](int r, int a, int b) -> bool {
            return r*r >= (a*a + b*b);
        };

        // Case 1: rectangle inside circle
        if (isPointInsideOriginCenteredCircle(radius, x1, y1)) return true;

        // Case 2: Circle inside rectangle
        if(isPointInsideRectangle(x1, y1, x2, y2, 0, 0)) return true;

        // Case 3: onde of the boundaries of the rectangle intersects the circle
        vector<vector<int>> borders = {
            {x1, y1, y2}, {x2, y1, y2}, {y1, x1, x2}, {y2, x1, x2}
        };
        for(vector<int>& border : borders) {
            int fixed = border[0];
            int start = border[1];
            int end = border[2];

            int startImage = (radius*radius - fixed*fixed - start*start);
            int endImage = (radius*radius - fixed*fixed - end*end);

            if(startImage >= 0 || endImage >= 0) return true;
            if(radius*radius >= fixed*fixed && start < 0 && end > 0) return true;
        }

        return false;
    }
};
