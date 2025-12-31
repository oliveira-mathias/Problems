class Solution {
public:
    int maxProduct(vector<int>& nums) {
        const int n = nums.size();
        // Handling edge case
        if(n == 1) return nums[0];

        int LP = 0; // Largest positive product so far
        int LN = 0; // Largest negative product so far
        int maxSeen = nums.back();


        for(int i=n-1; i>=0; --i) {
            int newLP, newLN;
            if(nums[i] > 0) {
                newLP = nums[i]*LP;
                newLN = nums[i]*LN;
            }
            else if(nums[i] < 0) {
                newLP = nums[i]*LN;
                newLN = nums[i]*LP;
            }
            else {
                newLP = 0;
                newLN = 0;
            }

            // Handling the case where we need to start a new sequence
            if(newLP == 0 && nums[i] > 0) {
                newLP = nums[i];
            }
            if(newLN == 0 && nums[i] < 0) {
                newLN = nums[i];
            }

            LP = newLP;
            LN = newLN;

            maxSeen = max(LP, maxSeen);
        }

        return maxSeen;
    }
};
