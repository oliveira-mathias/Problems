class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int minimumDistance(vector<int>& nums) {
        unordered_map<int, vector<int>> buckets;
        // Separating the indicies into buckets
        for(int i=0; i<nums.size(); ++i) {
            buckets[nums[i]].push_back(i);
        }

        // Computing the minimum distance
        int minDist = 3*nums.size();
        for(const auto& [_, indices] : buckets) {
            for(int i=0; i+2<indices.size(); ++i) {
                minDist = min(minDist, 2*(indices[i+2]-indices[i]));
            }
        }
        return (minDist==3*nums.size()) ? -1 : minDist;
    }
};
