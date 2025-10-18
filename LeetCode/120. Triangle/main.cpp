class Solution {
  public:
  int minimumTotal(vector<vector<int>>& triangle) {
    int rows = triangle.size();

    vector<int> p1 = vector<int>(rows);
    vector<int> p2 = triangle.back();

    for(int i=rows-2; i>=0; i--) {
      for(int j = 0; j<i+1; j++) {
        p1[j] = triangle[i][j] + min(p2[j], p2[j+1]);
      }

      // swap the buffers
      swap(p1, p2);
    }

    return p2[0];
  }
};
