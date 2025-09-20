class Solution {
  long long GCD(long long A, long long B) {
      if(B==0) {
          return A;
      }

      // Recursive step
      long long r = A % B;
      return GCD(B, r);
  }
  public:
  vector<int> replaceNonCoprimes(vector<int>& nums) {
      stack<long long> s;

      for(long long num : nums) {
          long long gcd = 2; // dummy value

          // pop untill gcd = 1 or stack is empty
          while(!s.empty() && gcd > 1) {
              gcd = GCD(s.top(), num);
              if(gcd > 1) {
                  num = (s.top()*num)/gcd;
                  s.pop();
              }
          }

          s.push(num);
      }

      vector<int> sol;
      while(!s.empty()) {
          sol.push_back(s.top());
          s.pop();
      }

      reverse(sol.begin(), sol.end());

      return sol;
  }
};
