class Fancy {
    static constexpr int P = 1000000007;
    vector<int> nums;
    // A*nums[i] + B
    vector<pair<int, int>> coef;
    long long A, B;
public:
    Fancy() : A(1), B(0) {}
    
    // Time: O(1)
    void append(int val) {
        nums.push_back(val);
        coef.emplace_back(A, B);
    }
    
    // Time: O(1)
    void addAll(int inc) {
        if(nums.empty()) return;
        B = (B + inc) % P;
    }
    
    // Time: O(1)
    void multAll(int m) {
        if(nums.empty()) return;
        A = (A * m) % P;
        B = (B * m) % P;
    }
    
    // Time: O(log(AOld))
    int getIndex(int idx) {

        if(idx >= nums.size()) return -1;

        const auto getInv = [](const int a, const int p) -> long long {
            int exp = p-2;
            long long currPow = a;
            long long inv = 1;

            while(exp) {
                if(exp & 1U) {
                    inv = (inv * currPow) % P;
                }
                currPow = (currPow * currPow) % P;
                exp >>= 1;
            }

            return inv;
        };

        const auto [AOld, BOld] = coef[idx];
        long long AOldInv = getInv(AOld, P);

        long long r = (AOldInv * A) % P;
        
        int ans = (r*nums[idx]) % P;
        ans = (ans + B - r*BOld) % P;
        return (ans >= 0) ? ans : (ans + P);
    }
};

/**
 * Your Fancy object will be instantiated and called as such:
 * Fancy* obj = new Fancy();
 * obj->append(val);
 * obj->addAll(inc);
 * obj->multAll(m);
 * int param_4 = obj->getIndex(idx);
 */
