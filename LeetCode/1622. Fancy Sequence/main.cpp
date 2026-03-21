class Fancy {
    static constexpr int MAX_SIZE = 100000;
    static constexpr int MAX_SIZE_ROOT = 317;
    static constexpr int MOD = 1000000007;
    vector<int> nums;
    // A*nums + b
    vector<pair<long long, long long>> numsCoeff;
    vector<pair<long long, long long>> binCoeff;
public:
    // Time: O(1)
    Fancy() {
        nums.reserve(MAX_SIZE);
        numsCoeff.reserve(MAX_SIZE);
        binCoeff.reserve(MAX_SIZE_ROOT);
    }
    
    // Time: O(1)
    void append(int val) {
        nums.push_back(val);
        numsCoeff.emplace_back(1, 0);
        int bin = nums.size() / MAX_SIZE_ROOT;
        if(bin > binCoeff.size()) {
            binCoeff.emplace_back(1, 0);
        }
    }
    
    // Time: O(sqrt(n))
    void addAll(int inc) {
        int bin = nums.size() / MAX_SIZE_ROOT;
        for(int i=0; i<bin; ++i) {
            binCoeff[i].second = (binCoeff[i].second + inc)%MOD;
        }

        for(int i=bin*MAX_SIZE_ROOT; i<nums.size(); ++i) {
            numsCoeff[i].second = (numsCoeff[i].second + inc)%MOD;
        }
    }
    
    // Time: O(sqrt(n))
    void multAll(int m) {
        int bin = nums.size() / MAX_SIZE_ROOT;
        for(int i=0; i<bin; ++i) {
            binCoeff[i].first = (binCoeff[i].first * m)%MOD;
            binCoeff[i].second = (binCoeff[i].second * m)%MOD;
        }

        for(int i=bin*MAX_SIZE_ROOT; i<nums.size(); ++i) {
            numsCoeff[i].first = (numsCoeff[i].first * m)%MOD;
            numsCoeff[i].second = (numsCoeff[i].second * m)%MOD;
        }
    }
    
    // Time: O(1)
    int getIndex(int idx) {
        if(idx >= nums.size()) return -1;

        int val = nums[idx];
        // local coef
        val = (val*numsCoeff[idx].first)%MOD;
        val = (val + numsCoeff[idx].second)%MOD;

        // bin coeff
        int bin = idx / MAX_SIZE_ROOT;
        if(bin < binCoeff.size()) {
            val = (val*binCoeff[bin].first)%MOD;
            val = (val + binCoeff[bin].second)%MOD;
        }

        return val;
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
