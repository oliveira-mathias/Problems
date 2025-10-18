class Solution {
    const int gridSize = 9;
    vector<char> valToChar = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    bool backtrack(vector<vector<char>>& board, vector<int>& rowState, vector<int>& colState, vector<int>& tileState, vector<int>& emptySlots, int current) {

        // Base case
        if(current == emptySlots.size()) {
            return true;
        }

        // Getting empty slot
        int i = emptySlots[current]/gridSize;
        int j = emptySlots[current]%gridSize;
        int tileCoord = 3*(i/3) + (j/3);


        // Try to insert a value on the grid
        for(int val=1; val<=gridSize; val++) {
            if(!(
                (rowState[i] & (1<<val))
                | (colState[j] & (1<<val))
                | (tileState[tileCoord] & (1<<val))
            )
            ) {
                board[i][j] = valToChar[val];
                rowState[i] |= (1<<val);
                colState[j] |= (1<<val);
                tileState[tileCoord] |= (1<<val);

                if(backtrack(board, rowState, colState, tileState, emptySlots, current+1)) {
                    return true;
                }

                rowState[i] &= ~(1<<val);
                colState[j] &= ~(1<<val);
                tileState[tileCoord] &= ~(1<<val);
                board[i][j] = '.';
            }
        }

        // All attempts failed
        return false;
    }
public:
    void solveSudoku(vector<vector<char>>& board) {

        vector<int> rowState = vector<int>(gridSize, 0);
        vector<int> colState = vector<int>(gridSize, 0);
        vector<int> tileState = vector<int>(gridSize, 0);

        vector<int> emptySlots;

        // Initializing the states
        for(int i=0; i<gridSize; i++) {
            for(int j=0; j<gridSize; j++) {
                if(board[i][j]=='.') {
                    emptySlots.push_back(gridSize*i + j);
                    continue;
                }

                int tileCoord = 3*(i/3) + (j/3);
                int val = board[i][j]-'0';
                rowState[i] |= 1<<(val);
                colState[j] |= 1<<(val);
                tileState[tileCoord] |= 1<<(val);
            }
        }

        // Backtracking a solution
        backtrack(board, rowState, colState, tileState, emptySlots, 0);
    }
};
