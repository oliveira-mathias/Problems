// Solution: sort the array and choose a window of size k
// One of the windows is an optimal solution
// Suppose the array A is sorted
// Suppose that {A[i1], ..., A[ik]} is an optimal solution and that i1 < ... < ik
// Suppose ij is the first index where the optimal solution disagrees with 
// the algorithm.
// Then clearly we can replace A[ij] by A[ik - (k-j)] and still have an optimal solution
// Which contradicts our hypothesis
class Solution {
public:
    // Time: O(n log(n))
    // Space: O(log(n))
    int minimumDifference(vector<int>& nums, int k) {
        if(k==1) return 0;

        sort(nums.begin(), nums.end());

        int minDiff = nums.back() - nums.front();

        for(int i=0, j=k-1; j<nums.size(); ++i, ++j) {
            minDiff = min(minDiff, nums[j] - nums[i]);
        }

        return minDiff;
    }
};

