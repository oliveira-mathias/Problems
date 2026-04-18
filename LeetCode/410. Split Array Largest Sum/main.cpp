class Solution {
public:
    // Time: O(n log(C)), C = sum{nums[i]} - max{nums[i]}
    // Space: O(1)
    int splitArray(vector<int>& nums, int k) {
        int left = 0, right = 1;

        for(int num : nums) {
            left = max(left, num);
            right += num;
        }
        
        const auto partition = [&nums, k](int maxSum) -> bool {
            int currSum = maxSum + 1;
            int usedPartitions = 0;

            for(int i=0; i<nums.size(); ++i) {
                if(currSum + nums[i] <= maxSum) {
                    currSum += nums[i];
                }
                else if(nums[i] > maxSum) {
                    return false;
                }
                else if(usedPartitions < k) {
                    // We start a new partition
                    usedPartitions++;
                    currSum = nums[i];
                }
                else {
                    // We already used all the partitions
                    return false;
                }
            }

            return true;
        };

        while(left < right) {
            int m = left + (right - left)/2;

            if(partition(m)) {
                right = m;
            }
            else {
                left = m + 1;
            }
        }

        return left;
    }
};
