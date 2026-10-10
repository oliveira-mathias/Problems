class Solution {
public:
    // Time: O(n + maxDiff)
    // SPace: O(maxDiff)
    long long minSumSquareDiff(const vector<int>& nums1, const vector<int>& nums2, int k1, int k2) {
        int n = nums1.size();
        int maxDiff = 0;
        for(int i=0; i<n; ++i) {
            maxDiff = max(maxDiff, abs(nums1[i]-nums2[i]));
        }
        vector<int> diffs(maxDiff+1);
        for(int i=0; i<n; ++i) {
            int diff = abs(nums1[i]-nums2[i]);
            diffs[diff]++;
        }

        int ops = k1+k2;
        for(int currDiff = maxDiff; currDiff>0 && ops>0; --currDiff) {
            int movable = min(ops, diffs[currDiff]);
            diffs[currDiff-1] += movable;
            diffs[currDiff] -= movable;
            ops -= movable;
        }
        long long ans = 0;
        for(long long currDiff=maxDiff; currDiff>0; --currDiff) {
            ans += currDiff*currDiff*diffs[currDiff];
        }
        return ans;
    }
};
