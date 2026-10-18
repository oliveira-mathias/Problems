class Solution {
public:
    // Time: O(n log(n))
    // Space: O(log(n))
    int maxSubArray(const vector<int>& nums) {
        const auto divideEtImpera = [&nums](this auto&& divideEtImpera, int l, int r) -> int {
            // Base case
            if(l == r) {
                return nums[l];
            }

            // Recursive step
            int m = l + (r-l)/2;
            int maxLeft = divideEtImpera(l, m);
            int maxRight = divideEtImpera(m+1, r);

            // Best Left Part [    { }|        ]
            int maxLeftPart = nums[m];
            int currLeftSum = nums[m];
            for(int i=m-1; i>=l; --i) {
                currLeftSum += nums[i];
                maxLeftPart = max(maxLeftPart, currLeftSum);
            }
            // Best Right Part [      |{    }  ]
            int maxRightPart = nums[m+1];
            int currRightSum = nums[m+1];
            for(int i=m+2; i<=r; ++i) {
                currRightSum += nums[i];
                maxRightPart = max(maxRightPart, currRightSum);
            }

            return max({maxLeft, maxRight, maxLeftPart+maxRightPart});
        };
        return divideEtImpera(0, nums.size()-1);
    }
};
