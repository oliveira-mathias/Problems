class Solution {
public:
    // Time: O(n log(n) + n log(max{position[i]}))
    // Space: O(log(n))
    int maxDistance(vector<int>& position, int m) {
        sort(position.begin(), position.end());

        int l = 1;
        int r = position.back() - position.front() + 1;

        const auto maxBasketSplit = [&position](int T) -> int {
            int count = 1;
            int last = position[0];

            for(int i=1; i<position.size(); ++i) {
                if(position[i]-last >= T) {
                    last = position[i];
                    count++;
                }
            }

            return count;
        };
        int lowerBound;
        while(l < r) {

            int middle = l + (r-l)/2;

            if(maxBasketSplit(middle) >= m) {
                lowerBound = middle;
                l = middle + 1;
            }
            else {
                r = middle;
            }
        }
        return lowerBound;
    }
};
