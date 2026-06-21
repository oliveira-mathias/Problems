class Solution {
public:
    double angleClock(int hour, int minutes) {
        double minutePointerAngle = minutes*6;
        double hourPointerAngle = (hour == 12) ? 0 : hour*30;
        // Adjusting angle due to minutes
        hourPointerAngle += minutes*0.5;

        double angle1 = max(hourPointerAngle, minutePointerAngle) - min(hourPointerAngle, minutePointerAngle);
        double angle2 = 360 - angle1;
        return min(angle1, angle2);
    }
};
