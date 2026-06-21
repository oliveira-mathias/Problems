class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int largestAltitude(vector<int>& gain) {
        int maxHeight = 0;
        int currHeight = 0;
        for(int delta : gain) {
            currHeight += delta;
            maxHeight = max(maxHeight, currHeight);
        }
        return maxHeight;
    }
};
