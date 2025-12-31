class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        auto countLeq = [&nums](int k) {
            int count = 0;
            for(int num : nums) {
                if(num <= k) {
                    count++;
                }
            }
            return count;
        };

        int left = 0;
        int right = nums.size();
        while(left < right) {
            int mid = left + (right - left)/2;
            int bottomIntervalLength = mid - left + 1;
            if(countLeq(mid) > mid) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        return left;
    }
};
