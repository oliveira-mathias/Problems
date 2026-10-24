class Solution {
public:
    // Time: O(days.size())
    // SPace: O(1)
    int countDaysTogether(const string& arriveAlice, const string& leaveAlice, const string& arriveBob, const string& leaveBob) {
        const int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        const auto dateToDay = [&days](const string& date) -> int {
            constexpr int monthField1 = 0;
            constexpr int monthField2 = 1;
            constexpr int dayField1 = 3;
            constexpr int dayField2 = 4;

            int month = (date[monthField1]-'0')*10 + (date[monthField2]-'0');
            int day = (date[dayField1]-'0')*10 + (date[dayField2]-'0');

            int ans = 0;
            for(int i=1; i<month; ++i) {
                ans += days[i-1];
            }
            ans += day;
            return ans;
        };

        int aliceInitialDay = dateToDay(arriveAlice);
        int aliceLastDay = dateToDay(leaveAlice);
        int bobInitialDay = dateToDay(arriveBob);
        int bobLastDay = dateToDay(leaveBob);

        int start = max(aliceInitialDay, bobInitialDay);
        int end = min(aliceLastDay, bobLastDay);
        return max(0, end-start+1);
    }
};
