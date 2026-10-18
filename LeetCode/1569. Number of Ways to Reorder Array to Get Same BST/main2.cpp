class Solution {
public:
    // Time: O(n²)
    // Space: O(n²)
    int numOfWays(const vector<int>& nums) {
        constexpr int MOD = 1000000007;
        int m = nums.size();
        vector<vector<int>> comb(m+1, vector<int>(m+1));
        // Base case (k=0)
        for(int n=0; n<=m; ++n) {
            comb[n][0] = 1;
        }
        for(int n=1; n<=m; ++n) {
            for(int k=1; k<=n; ++k) {
                comb[n][k] = (comb[n-1][k-1] + comb[n-1][k])%MOD;
            }
        }
        
        const auto computeWays = [&nums, &comb](this auto&& computeWays, const vector<int>& elements) -> long long {
            // Base case
            if(elements.empty()) {
                return 1;
            }

            // Recursive case
            // Partitioning Elements
            int root = elements[0];
            vector<int> leftElements, rightElements;
            leftElements.reserve(elements.size() - 1);
            rightElements.reserve(elements.size() - 1);
            for(int i=1; i<elements.size(); ++i) {
                if(elements[i] < root) {
                    leftElements.push_back(elements[i]);
                }
                else {
                    rightElements.push_back(elements[i]);
                }
            }

            long long leftWays = computeWays(leftElements);
            long long rightWays = computeWays(rightElements);
            int n = leftElements.size() + rightElements.size();
            int k = leftElements.size();
            long long mergeFactor = comb[n][k];
            long long ans = (leftWays*rightWays)%MOD;
            ans = (ans*mergeFactor)%MOD;
            return ans;
        };
        long long validPerm = computeWays(nums);
        validPerm--;
        if(validPerm < 0) {
            validPerm += MOD;
        }
        return validPerm;
    }
};
