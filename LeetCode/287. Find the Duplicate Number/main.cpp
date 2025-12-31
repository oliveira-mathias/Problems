class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int slow = 0;
        int fast = 0;
        do {
            slow = nums[slow];
            fast = nums[fast];
            fast = nums[fast];
        } while(fast != slow);

        // Here we find the entry of the loop
        int aux = 0;
        while(aux != slow) {
            aux = nums[aux];
            slow = nums[slow];
        }

        return slow;
    }
};
