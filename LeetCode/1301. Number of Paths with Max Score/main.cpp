class Solution {
public:
    // Time: O(n²)
    // Space: O(n)
    vector<int> pathsWithMaxScore(vector<string>& board) {
        constexpr int MOD = 1000000007;
        int n = board.size();
        // [maxDist, maxNumPaths]
        vector<pair<int, long long>> currRow (n);
        vector<pair<int, long long>> nextRow (n);

        // Base case
        auto getWeight = [](char c) {
            if(c >= '1' && c <= '9') return c-'0';
            else return 0;
        };
        currRow[0] = {0, 1};
        for(int j=1; j<board[0].size(); ++j) {
            if(board[0][j] == 'X' || currRow[j-1].first==-1) {
                currRow[j] = {-1, 0};
            }
            else {
                currRow[j] = {currRow[j-1].first + getWeight(board[0][j]), 1}; 
            }
        }

        // Recursive step
        for(int i=1; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                int maxNeighWeight = -1;
                if(j > 0) {
                    maxNeighWeight = max(maxNeighWeight, nextRow[j-1].first);
                    maxNeighWeight = max(maxNeighWeight, currRow[j-1].first);
                }
                maxNeighWeight = max(maxNeighWeight, currRow[j].first);

                if(maxNeighWeight==-1 || board[i][j]=='X') {
                    nextRow[j] = {-1, 0};
                }
                else {
                    nextRow[j].first = maxNeighWeight + getWeight(board[i][j]);
                    nextRow[j].second = 0;
                    if(j > 0 && nextRow[j-1].first == maxNeighWeight) {
                        nextRow[j].second = (nextRow[j].second + nextRow[j-1].second) % MOD;
                    }
                    if(j > 0 && currRow[j-1].first == maxNeighWeight) {
                        nextRow[j].second = (nextRow[j].second + currRow[j-1].second) % MOD;
                    }
                    if(currRow[j].first == maxNeighWeight) {
                        nextRow[j].second = (nextRow[j].second + currRow[j].second) % MOD;
                    }
                }
            }
            swap(currRow, nextRow);
        }

        if(currRow[n-1].first == -1) {
            return {0, 0};
        }
        return {currRow[n-1].first, static_cast<int>(currRow[n-1].second)};
    }
};
