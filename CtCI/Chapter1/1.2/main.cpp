#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Let A denote the Alphabet size
// Let n1 denote s1.size()
// Let n2 denote s2.size()
// Time: O(n1 + n2 + A)
// Space: O(A)
bool CheckPermutation(const string& s1, const string& s2) {
  if(s1.size() != s2.size()) {
    return false;
  }

  constexpr int charMax = 256;
  vector<int> deltaHist (charMax, 0);

  // Building the Histogram
  for(unsigned char c : s1) {
    deltaHist[c]++;
  }
  for(unsigned char c : s2) {
    deltaHist[c]--;
  }

  // Compare Histogram
  for(int i=0; i<charMax; i++) {
    if(deltaHist[i] != 0) {
      return false;
    }
  }

  return true;
}

int main(int argc, char** argv) {
  if(argc < 3) {
    cout << "invalid input" << endl;
    return 1;
  }

  string s1 = argv[1];
  string s2 = argv[2];

  cout << CheckPermutation(s1, s2) << endl;
}
