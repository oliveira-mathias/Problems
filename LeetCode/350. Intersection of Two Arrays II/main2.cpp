class Solution {
public:
    // Time: O(n + m)
    // Space: O(min{n, m})
    vector<int> intersect(const vector<int>& nums1, const vector<int>& nums2) {
        const vector<int>& smaller = (nums1.size() < nums2.size()) ? nums1 : nums2;
        const vector<int>& bigger = (nums1.size() < nums2.size()) ? nums2 : nums1;

        unordered_map<int, int> freq;
        for(int num : smaller) {
            freq[num]++;
        }

        vector<int> ans;
        for(int num : bigger) {
            if(freq[num]) {
                ans.push_back(num);
                freq[num]--;
            }
        }
        return ans;
    }
};
