class Solution {
  bool isVowel(char c) {
      return (c=='a') || (c=='e') || (c=='i') || (c=='o') || (c=='u');
  }
  public:
  int maxFreqSum(string s) {
      constexpr int numLetters = 26;
      vector<int> freq(numLetters, 0);

      // Building the frequency list
      for(char c : s) {
          freq[c-'a']++;
      }

      int largestVowelFreq = 0;
      int largestNonVowelFreq = 0;
      for(char c='a'; c<='z'; c++) {
          if(isVowel(c)) {
              largestVowelFreq = max(largestVowelFreq, freq[c-'a']);
          }
          else {
              largestNonVowelFreq = max(largestNonVowelFreq, freq[c-'a']);
          }
      }

      return largestVowelFreq+largestNonVowelFreq;
  }
};
