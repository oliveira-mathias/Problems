class Solution {
public:
    // Time: O(n log(n))
    // Space: O(n)
    vector<int> arrayRankTransform(const vector<int>& arr) {
        if(!arr.size()) return vector<int>();
        // Create the sorted mask
        vector<int> index(arr.size());
        for(int i=0; i<index.size(); ++i) index[i] = i;
        sort(index.begin(), index.end(), 
        [&arr](int i, int j) {
            return arr[i] < arr[j];
        });

        // Create the ranks mask
        vector<int> ranks(arr.size());
        ranks[index[0]] = 1;
        for(int i=1; i<arr.size(); ++i) {
            ranks[index[i]] = (arr[index[i]] > arr[index[i-1]]) ? ranks[index[i-1]]+1 : ranks[index[i-1]];
        }
        return ranks;
    }
};
