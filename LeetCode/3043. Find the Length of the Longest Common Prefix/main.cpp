class Solution {
public:
    // Time: O(n log(n) + m log(m))
    // Space: O(log(n) + log(m))
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        auto lexicographicalOrder = [](int a, int b) {
            return to_string(a) < to_string(b);
        };
        
        sort(arr1.begin(), arr1.end(), lexicographicalOrder);
        sort(arr2.begin(), arr2.end(), lexicographicalOrder);

        int maxPrefix = 0;
        int i = 0;
        int j = 0;
        while(i < arr1.size() && j < arr2.size()) {
            const string si = to_string(arr1[i]);
            const string sj = to_string(arr2[j]);

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
