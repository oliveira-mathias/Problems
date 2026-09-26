class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minOperations(const vector<int>& nums, int x) {
        int n = nums.size();
        int target = -x;
        for(int num : nums) {
            target += num;
        }

        if(target < 0) return -1;

        int minNums = n+1;
        for(int start=0, end=0, currSum=0; start<n; currSum -= nums[start], start++) {
            while(currSum < target  && end < n) {
                currSum += nums[end];
                end++;
            }

            if(currSum == target) {
                cerr << "start=" << start << ", end=" << end << endl;
                minNums = min(minNums, n - (end - start + 1));
            }
        }
        return (minNums > n) ? -1 : minNums;
    }
};
