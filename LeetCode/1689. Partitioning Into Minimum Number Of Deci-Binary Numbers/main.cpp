class Solution {
public:
    int minPartitions(string n) {
        char maxDigit = '1';
        for(char c : n) {
            maxDigit = max(maxDigit, c);
        }
        return maxDigit - '0';
    }
};
