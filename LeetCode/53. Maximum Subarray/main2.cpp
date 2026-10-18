class Solution {
public:
    // Time: O(n)
    // Space: O(log(n))
    struct ResultObject {
        int maxSubArray;
        int totalSum;
        int maxPrefixSum;
        int maxSuffixSum;
    };
    int maxSubArray(const vector<int>& nums) {
        const auto divideEtImpera = [&nums](this auto&& divideEtImpera, int l, int r) -> ResultObject {
            // Base case
            if(l == r) {
                return {nums[l], nums[l], nums[l], nums[l]};
            }

            // Recursive step
            int m = l + (r-l)/2;
            ResultObject maxLeftObject = divideEtImpera(l, m);
            ResultObject maxRightObject = divideEtImpera(m+1, r);

            int maxLeft = maxLeftObject.maxSubArray;
            int maxRight = maxRightObject.maxSubArray;
            int maxCrossing = maxLeftObject.maxSuffixSum + maxRightObject.maxPrefixSum;

            int maxPrefix = max(maxLeftObject.maxPrefixSum, maxLeftObject.totalSum + maxRightObject.maxPrefixSum);
            int maxSuffix = max(maxRightObject.maxSuffixSum, maxLeftObject.maxSuffixSum + maxRightObject.totalSum);

            return {max({maxLeft, maxRight, maxCrossing}), maxLeftObject.totalSum + maxRightObject.totalSum, maxPrefix, maxSuffix};
            
        };
        return divideEtImpera(0, nums.size()-1).maxSubArray;
    }
};
