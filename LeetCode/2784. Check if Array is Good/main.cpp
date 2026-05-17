class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    bool isGood(vector<int>& nums) {
        int n = nums.size()-1;
        vector<int> freqs(n);
        
        for(int num :  nums) {
            if(num > n || num < 1) return false;
            freqs[num-1]++;
        }
        freqs[n-1]--;
        for(int freq : freqs) {
            if(freq != 1) return false;
        }
        return true;
    }
};
