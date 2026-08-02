class Solution {
public:
    // TIme: O(n log(n))
    // Space: O(log(n))
    bool asteroidsDestroyed(int mass, vector<int>& asteroids) {
        sort(asteroids.begin(), asteroids.end());

        long long currMass = mass;
        for(int asteroid : asteroids) {
            if(asteroid > currMass) {
                return false;
            }
            else {
                currMass += asteroid;
            }
        }
        return true;
    }
};
