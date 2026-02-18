class Solution {
public:
    vector<string> readBinaryWatch(int turnedOn) {
        vector<string> res;
        constexpr int numBitsInWatch = 10;

        // In this case there is no solution
        if(turnedOn > 8) {
            return res;
        }

        auto buildString = [](vector<string>& res, unsigned timeMask) {
            unsigned minutes = timeMask & 0x0000003fU;
            unsigned hours = timeMask >> 6;

            if(hours > 11 || minutes > 59) return;

            string newHour;

            unsigned hoursFirstDigit = hours / 10;
            unsigned hoursSecondDigit = hours % 10;
            
            if(hoursFirstDigit > 0) {
                newHour += '1'; 
            }
            
            newHour += '0' + hoursSecondDigit;

            newHour += ':';

            unsigned minFirstDigit = minutes / 10;
            unsigned minSecondDigit = minutes % 10;

            newHour += '0' + minFirstDigit;
            newHour += '0' + minSecondDigit;

            res.emplace_back(newHour);
        };

        auto backtrack = [&res, &buildString, numBitsInWatch](unsigned currMask, int toSelect, int start, auto&& self) {
            // Base case
            if(toSelect == 0) {
                buildString(res, currMask);
                return;
            }

            // Recursive case
            for(int i=start; i<numBitsInWatch; ++i) {
                unsigned selectedMask = (1U << i);
                unsigned newMask = currMask | selectedMask;

                self(newMask, toSelect-1, i+1, self);
            }
        };

        backtrack(0U, turnedOn, 0, backtrack);
        return res;
    }
};
