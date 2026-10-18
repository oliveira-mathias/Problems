class Solution {
public:
    // Time: O(n²)
    // Space: O(n²)
    int numOfWays(const vector<int>& nums) {
        constexpr int MOD = 1000000007;
        const auto invModP = [](long long a, int p) -> long long {
            long long ans = 1;
            p -= 2;
            while(p) {
                if(p & 1U) {
                    ans = (ans*a)%MOD;
                }
                p >>= 1;
                a = (a*a) % MOD;
            }
            return ans;
        };
        const auto combModP = [&invModP](int n, int k, int p) -> long long {
            long long num = 1;
            long long dem = 1;
            for(int i=1; i<=k; ++i) {
                num = (num*(n-i+1))%p;
                dem = (dem*i)%p;
            }
            long long demInv = invModP(dem, p);
            return (num*demInv)%p;
        };
        const auto computeWays = [&nums, &combModP](this auto&& computeWays, const vector<int>& elements) -> long long {
            // Base case
            if(elements.empty()) {
                return 1;
            }

            // Recursive case
            // Partitioning Elements
            int root = elements[0];
            vector<int> leftElements, rightElements;
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
            int k = min(leftElements.size(), rightElements.size());
            long long mergeFactor = combModP(n, k, MOD);
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
