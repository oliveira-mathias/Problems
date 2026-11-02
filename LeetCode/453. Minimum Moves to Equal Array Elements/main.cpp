class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minMoves(vector<int>& nums) {
        int n = nums.size();
        int sum = 0;
        int minElement = nums[0];
        for(int num : nums) {
            sum += num;
            minElement = min(minElement, num);
        }
        // Solving th linear system of equations
        return sum - n*minElement;
    }
};
