class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int maximumProduct(vector<int>& nums) {
        int n = nums.size();
        int smallest = numeric_limits<int>::max();
        int smallest2 = numeric_limits<int>::max();
        int greatest = numeric_limits<int>::min();
        int greatest2 = numeric_limits<int>::min();
        int greatest3 = numeric_limits<int>::min();

        for(int num : nums) {
            // Tracking larger elements
            if(num > greatest) {
                // greatest3 greatest2 greatest -> greatest2 greatest num
                greatest3 = greatest2;
                greatest2 = greatest;
                greatest = num;
            }
            else if(num > greatest2) {
                // greatest3 greatest2 greatest -> greatest2 num greatest
                greatest3 = greatest2;
                greatest2 = num;
            }
            else if(num > greatest3) {
                // greatest3 greatest2 greatest -> num greatest2 greatest
                greatest3 = num;
            }

            // Tracking smaller elements
            if(num < smallest) {
                // smallest smallest2 -> num smallest
                smallest2 = smallest;
                smallest = num;
            }
            else if(num < smallest2) {
                // smallest smallest2 -> smallest num
                smallest2 = num;
            }
        }

        int op1 = smallest*smallest2*greatest;
        int op2 = greatest3*greatest2*greatest;
        return max(op1, op2);
    }
};
