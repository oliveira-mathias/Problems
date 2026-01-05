class Solution {
  public:
  // Time: O(m³log(n))
  // Space: O(m²)
  // For asymptotic purposes we can treat m as a constant
  int numOfWays(int n) {
    constexpr int MOD = 1000000007;
    constexpr int m = 12;
    constexpr int colors = 3;

    // Base case
    if(n == 1) return 12;

    const vector<vector<int>> configs = {
      {0,1,2}, {0,2,1}, {1,0,2}, {1,2,0}, 
      {2,0,1}, {2,1,0}, {0,1,0}, {0,2,0},
      {1,0,1}, {1,2,1}, {2,0,2}, {2,1,2}
    };

    // Defining if two configs are compatible
    auto hasEdge = [colors](const vector<int>& v1, const vector<int>& v2) -> int {
      for(int i=0; i<colors; ++i) {
        if(v1[i]==v2[i]) {
          return 0;
        }
      }
      return 1;
    };

    // Matrixes for binary exponentiation
    // Note that all these matrices are initialized to the zero matrix
    vector<vector<int>> aux(m, vector<int>(m));
    // M is the transistion matrix
    vector<vector<int>> MPow(m, vector<int>(m));
    vector<vector<int>> expRes(m, vector<int>(m, 0));

    auto initMatrix = [&configs, &hasEdge, m](vector<vector<int>>& M) -> void {
      for(int i=0; i<m; ++i) {
        for(int j=0; j<m; ++j) {
          M[i][j] = hasEdge(configs[i], configs[j]);
        }
      }
    };

    auto initIdentityEntries = [m](vector<vector<int>>& M) {
      for(int i=0; i<m; ++i) {
        M[i][i] = 1;
      }
    };

    initMatrix(MPow);
    initIdentityEntries(expRes);

    // Matrix operations
    // lhs = (A*B)%MOD
    auto matrixMultiply = [m, MOD](vector<vector<int>>& lhs, vector<vector<int>>& A, 
                                vector<vector<int>>& B) -> void {
      for(int i=0; i<m; ++i) {
        for(int j=0; j<m; ++j) {
          long long sum = 0;
          for(int k=0; k<m; ++k) {
            long long prod = ((long long)A[i][k])*B[k][j];
            sum = (sum + prod)%MOD;
          }
          lhs[i][j] = sum;
        }
      }
    };

    // Performing the binary exponentiation
    --n;
    while(n > 0) {
      if(n & 1) {
        matrixMultiply(aux, MPow, expRes);
        swap(aux, expRes);
      }

      matrixMultiply(aux, MPow, MPow);
      swap(aux, MPow);

      n >>= 1;
    }

    // Computing the final result
    int res = 0;
    for(int i=0; i<m; ++i) {
      for(int j=0; j<m; ++j) {
        res = (res + expRes[i][j])%MOD;
      }
    }

    return res;

  }
};
