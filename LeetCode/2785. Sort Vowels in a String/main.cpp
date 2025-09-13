// Use counting sort for vowels
class Solution {
    bool isVowel(char& c) {
        switch(c) {
            case 'A':
            case 'E':
            case 'I':
            case 'O':
            case 'U':
            case 'a':
            case 'e':
            case 'i':
            case 'o':
            case 'u':
                return true;
            default:
                return false;
        }
    }

    int vowelToInd(char& c) {
        switch(c) {
            case 'A':
                return 0;
            case 'E':
                return 1;
            case 'I':
                return 2;
            case 'O':
                return 3;
            case 'U':
                return 4;
            case 'a':
                return 5;
            case 'e':
                return 6;
            case 'i':
                return 7;
            case 'o':
                return 8;
            case 'u':
                return 9;
            default:
                return -1;
        }
    }
public:
    string sortVowels(string s) {
        constexpr int numVowels = 10;
        vector<int> vowelsCount(numVowels, 0);
        vector<char> indToVowel = {'A', 'E', 'I', 'O', 'U',
                                    'a', 'e', 'i', 'o', 'u'};


        // We pass counting vowels
        for(int i=0; i<s.length(); i++) {
            if(isVowel(s[i])) {
                vowelsCount[vowelToInd(s[i])]++;
            }
        }
        // Position vowels pointer
        int j;
        for(j=0; j<numVowels; j++) {
            if(vowelsCount[j] > 0) {
                break;
            }
        }
        // Pass replacing vowels
        for(int i=0; i<s.length(); i++) {
            if(isVowel(s[i])) {
                // Replace by current vowel
                s[i] = indToVowel[j];
                vowelsCount[j]--;
                // Reposition vowels pointer
                while(j<numVowels && vowelsCount[j] == 0) {
                    j++;
                }
            }
        }

        return s;
    }
};
