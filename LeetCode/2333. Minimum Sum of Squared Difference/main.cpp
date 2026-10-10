class Solution {
public:
    // Time: O(n log(max{nums1[i]-nums2[i]}))
    // SPace: O(1)
    long long minSumSquareDiff(const vector<int>& nums1, const vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        int maxNums = nums1[0];
        for(int i=0; i<n; ++i) {
            maxNums = max({maxNums, nums1[i], nums2[i]});
        }

        const auto canCapVecDiffAtM = [](const vector<int>& vec1, const vector<int>& vec2, long long ops, int m) -> long long {
            for(int i=0; i<vec1.size(); ++i) {
                int num = abs(vec1[i]-vec2[i]);
                if(num > m) {
                    ops -= num-m;
                }
            }
            return ops;
        };
        int l = 0;
        int r = maxNums + 1;
        while(l < r) {
            int m = l + (r-l)/2;
            if(canCapVecDiffAtM(nums1, nums2, k1+k2, m) >= 0) {
                r = m;
            }
            else {
                l = m+1;
            }
        }
        // Early exit
        if(r==0) return 0;
        // Computing the sum
        long long freeOperations = canCapVecDiffAtM(nums1, nums2, k1+k2, r);
        long long ans = 0;
        long long M = r;
        for(int i=0; i<n; ++i) {
            long long num = abs(nums1[i]-nums2[i]);
            // We can cap the number at M
            if(num >= M) {
                num = M;
            }
            // Maybe we can reduce one unit in this num
            if(num==M && freeOperations>0) {
                freeOperations--;
                num--;
            }
            // Sum the final result
            ans += num*num;
        }
        return ans;
    }
};
