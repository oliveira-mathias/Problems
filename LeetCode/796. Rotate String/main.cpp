class Solution {
public:
    // Time: O(mn)
    // Space: O(1)
    bool rotateString(const string& s, const string& goal) {
        if(s.size() != goal.size()) return false;

        auto matchRotated = [&s, &goal](int offset) -> bool {
            for(int i=0; i<s.size(); ++i) {
                int rotatedIndex = (i + offset) % s.size();
                if(s[rotatedIndex] != goal[i]) return false;
            }
            return true;
        };

        for(int offset=0; offset<s.size(); ++offset) {
            if(matchRotated(offset)) return true;
        }
        return false;
    }
};
