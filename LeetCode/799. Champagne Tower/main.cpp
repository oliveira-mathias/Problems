class Solution {
public:
    double champagneTower(int poured, int query_row, int query_glass) {
        if(query_row == 0) {
            return (poured >= 1) ? 1 : 0;
        }
        
        const int depth = query_row + 1;

        vector<double> currRowExcedings(depth, 0);
        vector<double> nextRowExcedings(depth, 0);
        vector<double> nextRowStatus(depth, 0);

        // Base step of the DP
        if(poured > 1) {
            currRowExcedings[0] = poured-1;
        }
        else {
            currRowExcedings[0] = 0;
        }

        for(int i=1; i<depth; ++i) {
            for(int j=0; j<=i; ++j) {
                double glassAmount = 0;
                if(j > 0) {
                    glassAmount += currRowExcedings[j-1]/2;
                }
                if(j < i) {
                    glassAmount += currRowExcedings[j]/2;
                }
                if(glassAmount >= 1 - 1e-16) {
                    nextRowStatus[j] = 1;
                    nextRowExcedings[j] = glassAmount - 1;
                }
                else {
                    nextRowStatus[j] = glassAmount;
                    nextRowExcedings[j] = 0;
                }
            }

            swap(currRowExcedings, nextRowExcedings);
        }

        return nextRowStatus[query_glass];
    }
};
