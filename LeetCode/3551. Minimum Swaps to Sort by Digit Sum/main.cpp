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
        const auto DFS = [&idxs](this auto&& DFS, int node) -> int {
            // Base case
            if(idxs[node] < 0) {
                return 0;
            }
            // Recursive step
            int neigh = idxs[node];
            idxs[node] = -1;
            return 1 + DFS(neigh);
        };
        int moves = 0;
        for(int i=0; i<nums.size(); ++i) {
            if(idxs[i] >= 0) {
                moves += DFS(i) - 1;
            }
        }
        return moves;
    }
};
