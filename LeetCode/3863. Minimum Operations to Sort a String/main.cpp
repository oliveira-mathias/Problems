class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minOperations(const string& s) {
        bool isSorted = true;
        char minChar = s[0];
        int firstMinChar = 0;
        char maxChar = s[0];
        int lastMaxChar = 0;
        for(int i=1; i<s.size(); ++i) {
            if(s[i-1] > s[i]) {
                isSorted = false;
            }
            if(minChar > s[i]) {
                minChar = s[i];
                firstMinChar = i;
            }
            if(maxChar <= s[i]) {
                maxChar = s[i];
                lastMaxChar = i;
            }
        }
        if(isSorted) return 0;
        if(s.size() == 2) return -1;
        // Case 1: first position is correct
        // Case 2: last position is correct
        if(s[0]==minChar || s.back()==maxChar) return 1;
        // Case 3: There is no proper subarray that touches last position and maxChar
        // or first position and minChar
        if((lastMaxChar==0) && (firstMinChar==s.size()-1)) return 3;
        // Case 4: There exists some subarray that touches the meximum element and the last position
        // or that touches the first element and the first position
        return 2;
    }
};
