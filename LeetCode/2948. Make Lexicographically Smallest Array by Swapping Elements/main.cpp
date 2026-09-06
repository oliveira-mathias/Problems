class Solution {
public:
    // Time: O(n log(n))
    // Space: O(n)
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();
        vector<int> index(n);
        iota(index.begin(), index.end(), 0);

        // Sort the index vector
        sort(index.begin(), index.end(),
        [&nums](int i, int j){
            return nums[i] < nums[j];
        });
        // Sort the nums vector
        sort(nums.begin(), nums.end());

        vector<int> res(n);
        for(int i=0; i<n;) {
            // Computing the window
            int j = i;
            int currentNum = nums[i];
            for(; j < n && nums[j] - currentNum <= limit; ++j) {
                currentNum = nums[j];
            }
            sort(index.begin() + i, index.begin() + j);

            for(int k=i; k<j; ++k) {
                res[index[k]] = nums[k];
            }

            i = j;
        }
        return res;
    }
};
