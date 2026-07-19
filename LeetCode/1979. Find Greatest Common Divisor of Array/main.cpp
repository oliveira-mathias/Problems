class Solution {
public:
    // Time: O(n + log(max{nums[i]}))
    // Space: O()
    int findGCD(v1ector<int>& nums) {
        const auto gcd = [](int a, int b){
            while(b) {
                int aux = a % b;
                a = b;
                b = aux;
            }
            return a;
        };

        int minVal = nums[0];
        int maxVal = nums[0];
        for(int num : nums) {
            minVal = min(minVal, num);
            maxVal = max(maxVal, num);
        }
        return gcd(minVal, maxVal);
    }
};
