class Solution {
public:
    // Time: O(n sqrt{n})
    // Space: O(1)
    int sortableIntegers(const vector<int>& nums) {
        const auto canSort = [](const vector<int>& nums, int k) -> bool {
            int lowerBound = numeric_limits<int>::min();
            for(int i=0; i<nums.size(); i+=k) {
                int ceilElement = numeric_limits<int>::max();
                int minElement = nums[i];
                int maxElement = nums[i];
                int gaps = 0;
                // Check if it is possible to merge subarrays
                if(nums[i] < lowerBound) return false;
                // Check if it is possible to sort subaarray
                for(int j=i+1; j<i+k; ++j) {
                    minElement = min(minElement, nums[j]);
                    maxElement = max(maxElement, nums[j]);
                    if(nums[j] < nums[j-1]) {
                        gaps++;
                        ceilElement = nums[i];
                    }
                    // Here the subarray itself can't be sorted
                    if(nums[j] > ceilElement) return false;
                }
                if(gaps > 1 || minElement < lowerBound) return false;
                lowerBound = maxElement;
            }
            return true;
        };
        int sum = 0;
        const int n = nums.size();
        for(int k=1; k*k<=n; ++k) {
            if(n%k==0) {
                int div1 = k;
                int div2 = n/k;
                if(canSort(nums, div1)) {
                    sum += div1;
                }
                // To avoid double count on the square root
                if(div1 != div2 && canSort(nums, div2)) {
                    sum += div2;
                }
            }
        }
        return sum;
    }
};
