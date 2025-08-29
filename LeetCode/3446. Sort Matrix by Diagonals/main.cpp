#include <iostream>
#include <vector>
#include <algorithm>

#define vector std::vector

class Solution {
public:
  vector<vector<int>> sortMatrix(vector<vector<int>>& grid) {
    int n = grid.size();
    int diag;
    vector<int> diagElements;

    for(diag=-n+1; diag<n; diag++) {
      diagElements.clear();

      // We select the elements of the diagonal
      int x, y;
      for(x=0; x<n; x++) {
        y = x + diag;
        if(y>=0 && y<n) {
          diagElements.push_back(grid[y][x]);
        }
      }

      // Sorting the elements
      if(diag<0) {
        sort(diagElements.begin(), diagElements.end());
      }
      else {
        sort(diagElements.begin(), diagElements.end(), std::greater<int>());
      }

      // Write back
      int i = 0;
      for(x=0; x<n; x++) {
        y = x+diag;
        if(y>=0 && y<n) {
          grid[y][x] = diagElements[i];
          ++i;
        }
      }
    }

    return grid;
  }
};


int main() {
  int n = 3;
  vector<vector<int>> M = {
    {1,7,3},
    {9,8,2},
    {4,5,6},
  };

  Solution s;
  s.sortMatrix(M);

  for(int i=0; i<n; i++) {
    for(int j=0; j<n; j++) {
      std::cout << M[i][j] << " ";
    }
    std::cout << std::endl;
  }
}
