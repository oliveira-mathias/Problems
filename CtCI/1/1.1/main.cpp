#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// isUnique: implement an algorithm to detect if an string has all unique characters.

bool isUnique(string& s) {
  constexpr int maxDistinctChars = 128;
  // We coun the frequency of every character
  vector<int> freq(maxDistinctChars, 0);

  // Build the frequency table
  for(const char& c : s) {
    freq[c]++;
  }

  // Check for repetitions
  for(int i=0; i<maxDistinctChars; i++) {
    if(freq[i] > 1) {
      return false;
    }
  }

  return true;
}

// Polished solution
bool isUnique(string& s) {
  constexpr int maxDistinctChars = 128;
  // We coun the frequency of every character
  vector<bool> appear(maxDistinctChars, false);

  // Build the frequency table
  for(const char c : s) {
    if(!appear[c]) {
      appear[c] = true;
    }
    else {
      return false;
    }
  }

  return true;
}

// What if you cannot use additional data structures?

bool isUnique(string s) {
  sort(s.begin(), s.end());

  char currChar = s[0];
  for(int i=1; i<s.size(); i++) {
    if(s[i]==currChar) {
      return false;
    }
  }

  return true;
}
