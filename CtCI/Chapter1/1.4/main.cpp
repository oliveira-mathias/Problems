#include <iostream>
#include <vector>
#include <string>

using namespace std;

unsigned char charToLower(char c) {
  if(c >= 'A' && c <= 'Z') {
    c = c-'A' + 'a';
  }

  return c;
}

bool PalindromePermutation(const string& s) {
  constexpr int maxChar = 256;
  vector<int> sCharHist(maxChar, 0);

  int spacesCount = 0;
  for(char c : s) {
    if(c == ' ') {
      spacesCount++;
      continue;
    }
    sCharHist[charToLower(c)]++;
  }

  // We count how many characters of the string have odd parity
  int oddParityCount = 0;
  const int numberOfNonSpaceChars = s.size() - spacesCount;
  const int oddParityLimit = (numberOfNonSpaceChars%2) ? 1 : 0;
  for(int i=0; oddParityCount <= oddParityLimit && i<maxChar; i++) {
    if(sCharHist[i]%2) {
      oddParityCount++;
    }
  }

  return (oddParityCount <= oddParityLimit);
}

int main(int argc, char** argv) {
  if(argc < 2) {
    return 1;
  }

  string s = argv[1];

  cout << PalindromePermutation(s) << endl;
}
