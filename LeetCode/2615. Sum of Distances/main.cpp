class Solution {
public:
    // Time: O(n)
    // Space: O(n)
    vector<long long> distance(vector<int>& nums) {
        int n = nums.size();
        unordered_map<int, vector<int>> elements;
        
        for(int i=0; i<nums.size(); ++i) {
            elements[nums[i]].push_back(i);
        }

        vector<long long> arr;
        arr.resize(n);

        for(const auto& [_, indices] : elements) {
            long long suffixSum = 0;
            for(int index : indices) suffixSum += index;

            long long prefixSum = 0;
            for(int i=0; i<indices.size(); ++i) {
                // Update sums
                long long index = indices[i];
                prefixSum += index;
                suffixSum -= index;

                int m = indices.size();
                arr[index] = ((i+1)*index - prefixSum) + (suffixSum - (m-1-i)*index);
            }
        }

        return arr;
    }
};
