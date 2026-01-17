class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        // We use append a sentinel at the stack
        vector<pair<int, int>> stack = {{-1, 0}};
        int maxArea = 0;

        for(int i=0; i<heights.size(); ++i) {
            int propagatedWidth = 0;
            // Pop ended rectangles
            while(heights[i] < stack.back().first) {
                const auto [height, width] = stack.back();
                propagatedWidth += width;
                maxArea = max(maxArea, height*(propagatedWidth));
                stack.pop_back();
            }


            const auto [currHeight, currWidth] = stack.back();
            if(heights[i] > currHeight) {
                stack.emplace_back(heights[i], propagatedWidth + 1);
            }
            else {
                // Here heights[i] == currHeight
                stack.back().second += propagatedWidth + 1;
            }

        }

        // Processing the elements that remainded in the stack
        // We don't process the sentinel
        while(stack.size() > 1) {
            const auto [height, width] = stack.back();
            maxArea = max(maxArea, height*width);
            stack.pop_back();
            stack.back().second += width;
        }

        return maxArea;
    }
};
