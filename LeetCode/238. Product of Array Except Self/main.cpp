class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    vector<int> productExceptSelf(const vector<int>& nums) {
        int n = nums.size();
        vector<int> ans(n);
        // We use ans to temporarilly hold the prefix product
        ans[0] = nums[0];
        for(int i=1; i<n; ++i) {
            ans[i] = nums[i]*ans[i-1];
        }
        // We compute the suffix product on the fly
        int mcc = 1;
        for(int i=n-1; i>0; --i) {
            ans[i] = mcc*ans[i-1];
            mcc *= nums[i];
        }
        ans[0] = mcc;

        return ans;
    }
};
