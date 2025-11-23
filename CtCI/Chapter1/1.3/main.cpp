#include <iostream>
#include <string>

using namespace std;

void URLify(string& s) {
  int spacesCount = 0;
  int nonSpacesCount = 0;
  int spacesBuffer = 0;
  int lastNonSpaceChar = -1;

  // Find the offsets
  for(int i=0; i<s.size(); i++) {
    if(s[i] == ' ') {
      spacesBuffer++;
    }
    else {
      spacesCount += spacesBuffer;
      spacesBuffer = 0;
      nonSpacesCount++;
      lastNonSpaceChar = i;
    }
  }

  if(lastNonSpaceChar == -1) return;

  int writePos = nonSpacesCount + 3*spacesCount - 1;
  int readPos = lastNonSpaceChar;

  // Here we replace the ' ' from the string
  // There is nothing to do when we dont have more spaces to process
  while(spacesCount > 0) {
    if(s[readPos] == ' ') {
      s[writePos] = '0';
      s[writePos-1] = '2';
      s[writePos-2] = '%';
      
      writePos -= 3;
      readPos--;
      spacesCount--;
    }
    else {
      s[writePos] = s[readPos];
      writePos--;
      readPos--;
    }
  }


}

int main(int argc, char** argv) {
  if(argc < 2) {
    return 1;
  }

  string s = argv[1];

  URLify(s);

  cout << s << endl;
}
