class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    bool stoneGameIX(const vector<int>& stones) {
        int zeroStones = 0;
        int oneStones = 0;
        int twoStones = 0;
        for(const int stone : stones) {
            switch(stone%3) {
                case 0:
                    zeroStones++;
                    break;
                case 1:
                    oneStones++;
                    break;
                case 2:
                    twoStones++;
                    break;
            }
        }

        bool aliceWins = false;
        if(zeroStones%2) {
            // Here Bob start playing
            if(oneStones + twoStones < 2) {
                aliceWins = false;
            }
            else {
                // Considering sequence 11[21]*
                if(oneStones > 0) {
                    aliceWins |= (oneStones >= 2) && (twoStones < oneStones-2);
                }
                // Considering sequence 22[12]*
                if(twoStones > 0) {
                    aliceWins |= (twoStones >= 2) && (twoStones-2 > oneStones);
                }
            }      
        }
        else {
            // Here Alice start playing
            // Alice wins if the stones have different weight
            if(oneStones + twoStones < 2) {
                aliceWins |= (oneStones == 1 && twoStones == 1);
            }
            else {
                // Considering sequence 11[21]*
                if(oneStones > 0) {
                    aliceWins |= (oneStones < 2) || (twoStones > oneStones-2);
                }
                // Considering sequence 22[12]*
                if(twoStones > 0) {
                    aliceWins |= (twoStones < 2) || (oneStones > twoStones-2);
                }
            }
        }
        
        return aliceWins;
    }
};
