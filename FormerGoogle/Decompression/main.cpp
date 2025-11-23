#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

bool isDigit(char c) {
  return (c >= '0') && (c<='9');
}

bool hasDigits(string& s, int start, int end) {
  return (start <= end) && isDigit(s[start]);
}

int buildString(string& ans, unordered_map<int, int>& bracesMap, string& s, int start, int end) {
  // Base case: The string does not contain digits
  if(!hasDigits(s, start, end)) {
    for(int i=start; i<=end; i++) {
      ans += s[i];
    }

    return (end - start + 1);
  }

  // Recursive step
  // Search for the prefix of numbers
  int numsEnd;
  for(numsEnd=start+1; numsEnd<=end; numsEnd++) {
    if(!isDigit(s[numsEnd])) {
      break;
    }
  }

  // Here s[start, end) is all digits
  int repNumber = 0;
  int currPow = 1;
  for(int i=numsEnd-1; i>=start; i--) {
    repNumber += (s[i] - '0')*currPow;
    currPow *= 10;
  }

  // We know that s[numsEnd] is '['
  int bracesClose = bracesMap[numsEnd];
  // We solve the recursive parts
  int ansCurrSize = ans.size();
  int appendedChars = buildString(ans, bracesMap, s, numsEnd+1, bracesClose-1);
  for(int i=0; i<repNumber-1; i++) {
    // Repeat the suffix the right number of times
    for(int j=0; j<appendedChars; j++) {
      ans += ans[ansCurrSize + j];
    }
  }

  appendedChars *= repNumber;
  appendedChars += buildString(ans, bracesMap, s, bracesClose+1, end);

  return appendedChars;
}

string decompress(string& s) {
  // Building the braces map
  unordered_map<int, int> bracesMap;
  stack<int> bracesStack;

  // We assume the string is valid
  for(int i=0; i<s.size(); i++) {
    if(s[i]=='[') {
      bracesStack.push(i);
    }
    else if(s[i]==']') {
      bracesMap[bracesStack.top()] = i;
      bracesStack.pop();
    }
  }

  // We build the compressed string recursively
  string ans = "";
  buildString(ans, bracesMap, s, 0, s.size()-1);

  return ans;
}

int main(int argc, char** argv) {
  if(argc < 2) {
    return 0;
  }

  string s = argv[1];

  cout << decompress(s) << endl;
}
