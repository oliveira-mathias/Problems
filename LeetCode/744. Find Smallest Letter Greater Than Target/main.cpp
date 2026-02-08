class Solution {
public:
    // Time: O(log(n))
    // Space: O(1)
    char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0;
        int right = letters.size();

        while(left < right) {
            int mid = left + (right-left)/2;

            if(letters[mid] > target) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        // No letter is greater than target
        if(left == letters.size()) {
            return letters[0];
        }
        else {
            return letters[left];
        }
    }
};
