class Solution {
public:
    // Time: O(n + m)
    // Space: O(1)
    vector<vector<int>> intervalIntersection(const vector<vector<int>>& firstList, const  vector<vector<int>>& secondList) {
        vector<vector<int>> ans;
        int i=0;
        int j=0;
        while(i<firstList.size() && j<secondList.size()) {
            int intersectionStart = max(firstList[i][0], secondList[j][0]);
            int intersectionEnd = min(firstList[i][1], secondList[j][1]);

            if(intersectionStart<=intersectionEnd) {
                ans.push_back({intersectionStart, intersectionEnd});
            }

            if(firstList[i][1] > secondList[j][1]) {
                j++;
            }
            else {
                i++;
            }
        }
        return ans;
    }
};
