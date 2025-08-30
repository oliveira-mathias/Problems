#include <iostream>
#include <vector>

#define vector std::vector

class Solution {
  bool checkRows(vector<vector<char>>& board) {
    int set;

    int row;
    for(row=0; row<board.size(); ++row) {
      set = 0;
      for(int col=0; col<board[row].size(); ++col) {
        if(board[row][col] != '.') {
          int digit = board[row][col] - '0';
          if(set & (1<<digit)) {
            return false;
          }
          else {
            set = set | (1 << digit);
          }
        }
      }
    }

    return true;
  }

  bool checkCols(vector<vector<char>>& board) {
    int set;

    int col;
    for(col=0; col<board.front().size(); ++col) {
      set = 0;
      for(int row=0; row<board.size(); ++row) {
        if(board[row][col] != '.') {
          int digit = board[row][col] - '0';
          if(set & (1<<digit)) {
            return false;
          }
          else {
            set = set | (1 << digit);
          }
        }
      }
    }

    return true;
  }

  bool checkTiles(vector<vector<char>>& board) {
    const int tileSize = 3;
    int set;

    int rowOffset;
    for(rowOffset=0; rowOffset<board.size()/tileSize; ++rowOffset) {
      for(int colOffset=0; colOffset<board.front().size()/tileSize; ++colOffset) {
        set = 0;
        int i, j;
        for(i=0; i<tileSize; ++i) {
          int row = rowOffset*tileSize + i;

          for(j=0; j<tileSize; ++j) {
            int col = colOffset*tileSize + j;

            if(board[row][col] != '.') {
              int digit = board[row][col] - '0';
              if(set & (1<<digit)) {
                return false;
              }
              else {
                set = set | (1 << digit);
              }
            }

          }
        }
      }
    }

    return true;
  }
public:
  bool isValidSudoku(vector<vector<char>>& board) {
    return checkRows(board) && checkCols(board) && checkTiles(board);
  }
};

int main() {
  vector<vector<char>> grid = {
    {'8','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'},
  };

  Solution s;
  std::cout << s.isValidSudoku(grid) << std::endl;
}
