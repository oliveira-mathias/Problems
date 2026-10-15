class Solution {
public:
    // Time: O(n + max{nums[i]})
    // Space: O(max{nums[i]})
    long long maxAlternatingSum(const vector<int>& nums) {
        constexpr int MAX_VAL = 40000;
        vector<int> freq(MAX_VAL+1);
        // Counting sort
        for(int num : nums) {
            freq[abs(num)]++;
        }

        long long ans = 0;
        int toSubtract = nums.size()/2;
        int toSum = toSubtract + (nums.size() % 2);
        for(int currVal = 0; currVal<=MAX_VAL && (toSubtract | toSum); currVal++) {
            int subTerms = min(toSubtract, freq[currVal]);
            freq[currVal] -= subTerms;
            toSubtract -= subTerms;

            int sumTerms = freq[currVal];
            toSum -= sumTerms;

            long long term = 1LL*currVal*currVal;
            ans += (sumTerms - subTerms)*term;
        }
        return ans;
    }
};
