class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    int maxSubarrayLength(const vector<int>& nums, int k) {
        unordered_map<int, int> freq;

        int maxSubArr = 0;
        for(int l=0, r=0; r<nums.size(); r++) {
            int currNum = nums[r];
            freq[currNum]++;

            while(freq[currNum] > k) {
                int lNum = nums[l];
                freq[lNum]--;
                l++;
            }

            maxSubArr = max(maxSubArr, r-l+1);
        }
        return maxSubArr;
    }
};
