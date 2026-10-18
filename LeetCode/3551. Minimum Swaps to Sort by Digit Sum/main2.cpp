class Solution {
public:
    // Time: O(n log(n))
    // Space: O(n)
    int minSwaps(const vector<int>& nums) {
        vector<int> digitsSum(nums.size());
        for(int i=0; i<nums.size(); ++i) {
            int sum = 0;
            int num = nums[i];
            while(num) {
                sum += num%10;
                num /= 10;
            }
            digitsSum[i] = sum;
        }
        vector<int> idxs(nums.size());
        iota(idxs.begin(), idxs.end(), 0);
        sort(idxs.begin(), idxs.end(),
        [&nums, &digitsSum](int a, int b) {
            int sumA = digitsSum[a], sumB = digitsSum[b];

            return (sumA < sumB) || ((sumA == sumB) && (nums[a] < nums[b]));
        });

        // We DFS the induced graph
        const auto cycleSize = [&idxs](int node) -> int {
            int size = 0;
            while(idxs[node] >= 0) {
                size++;
                int currNode = node;
                node = idxs[node];
                idxs[currNode] = -1;
            }
            return size;
        };
        int moves = 0;
        for(int i=0; i<nums.size(); ++i) {
            if(idxs[i] >= 0) {
                moves += cycleSize(i) - 1;
            }
        }
        return moves;
    }
};
