class Solution {
public:
    // Time: O(n log(nums[í]))
    // Space: O(n)
    int minMirrorPairDistance(vector<int>& nums) {
        unordered_map<int, int> lastSeen;

        int minDist = numeric_limits<int>::max();
        for(int i=0; i<nums.size(); ++i) {
            const auto reverseNum = [](int n) -> int {
                int mirrored = 0;
                for(; n > 0; n /= 10) {
                    int digit = n % 10;
                    mirrored = 10*mirrored + digit;
                }
                return mirrored;
            };

            int mirrored = reverseNum(nums[i]);
            if(lastSeen.contains(nums[i])) {
                minDist = min(minDist, i - lastSeen[nums[i]]);
            }
            lastSeen[mirrored] = i;
        }

        return minDist > nums.size() ? -1 : minDist;
    }
};
