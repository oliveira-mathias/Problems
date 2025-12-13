class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int countCollisions(string directions) {
        int colisions = 0;
        int streak = 0;

        // Swap from left to right
        for(int i=0; i<directions.size(); ++i) {
            if(directions[i]=='R') {
                streak++;
            }
            else {
                colisions += streak;
                streak = 0;
            }
        }

        // Swap from right to left
        streak = 0;
        for(int i=directions.size()-1; i>=0; --i) {
            if(directions[i]=='L') {
                streak++;
            }
            else {
                colisions += streak;
                streak = 0;
            }
        }

        return colisions;
    }
};
