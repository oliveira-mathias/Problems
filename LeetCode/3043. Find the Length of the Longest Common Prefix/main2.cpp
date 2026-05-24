class Solution {
public:
    // Time: O(n log(n) + m log(m))
    // Space: O(n + m)
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        vector<string> sarr1, sarr2;
        sarr1.reserve(arr1.size());
        sarr2.reserve(arr2.size());

        for(int num : arr1) sarr1.push_back(to_string(num));
        for(int num : arr2) sarr2.push_back(to_string(num));
        
        sort(sarr1.begin(), sarr1.end());
        sort(sarr2.begin(), sarr2.end());

        int maxPrefix = 0;
        int i = 0;
        int j = 0;
        while(i < sarr1.size() && j < sarr2.size()) {
            const string& si = sarr1[i];
            const string& sj = sarr2[j];

            int prefix;
            for(prefix=0; prefix<min(si.size(), sj.size()); ++prefix) {
                if(si[prefix]!=sj[prefix]) break;
            }
            maxPrefix = max(prefix, maxPrefix);

            if(si < sj) ++i;
            else ++j;
        }
        return maxPrefix;
    }
};
