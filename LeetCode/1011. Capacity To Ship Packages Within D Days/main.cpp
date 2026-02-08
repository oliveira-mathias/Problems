class Solution {
public:
    int shipWithinDays(vector<int>& weights, int days) {
        // We binary search the capacity of the ship
        auto computeDays = [&weights, days](int capacity) -> int {
            int usedDays = 1;
            int currentLoad = 0;
            for(int weight : weights) {
                if(weight + currentLoad <= capacity) {
                    // Place package on current ship
                    currentLoad += weight;
                }
                else {
                    // We book a new ship
                    usedDays++;
                    currentLoad = weight;
                }
            }
            return usedDays;
        };

        int left = 0;
        int right = 0;
        for(int weight : weights) {
            right += weight;
            left = max(left, weight);
        }

        while(left < right) {
            int mid = left + (right-left)/2;

            if(computeDays(mid) <= days) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }

        return left;
    }
};
