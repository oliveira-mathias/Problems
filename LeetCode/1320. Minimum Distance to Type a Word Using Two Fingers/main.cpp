class Solution {
public:
    // Time: O(n*alphaSize²)
    // Space: O(alphaSize²)
    int minimumDistance(const string& word) {
        int n = word.size();
        constexpr int alphaSize = 26;
        constexpr int gridWidth = 6;

        vector<vector<int>> DP(alphaSize, vector<int>(alphaSize));
        vector<vector<int>> DPPrev(alphaSize, vector<int>(alphaSize));

        int minCost = numeric_limits<int>::max();
        for(int i=n-1; i>=0; --i) {
            int letterPos = word[i] - 'A';

            const auto computeDist = [gridWidth](int pos1, int pos2) -> int {
                int x1 = pos1 / gridWidth;
                int y1 = pos1 % gridWidth;

                int x2 = pos2 / gridWidth;
                int y2 = pos2 % gridWidth;

                return abs(x1 - x2) + abs(y1 - y2);
            };

            for(int pos1=0; pos1<alphaSize; ++pos1) {
                for(int pos2=0; pos2<alphaSize; ++pos2) {
                    int option1 = computeDist(pos1, letterPos) + DPPrev[letterPos][pos2];
                    int option2 = computeDist(pos2, letterPos) + DPPrev[pos1][letterPos];
                    DP[pos1][pos2] = min(option1, option2);

                    // Collect the final answer
                    if(i==0) {
                        minCost = min(minCost, DP[pos1][pos2]);
                    }
                }
            }

            swap(DP, DPPrev);
        }

        return minCost;
    }
};
