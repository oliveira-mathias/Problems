class Solution {
public:
  int maxBottlesDrunk(int numBottles, int numExchange) {
    int fullBottles = numBottles;
    int emptyBottles = 0;
    int drunkenBottles = 0;

    while(fullBottles > 0) {
      // Drink all bottles
      drunkenBottles += fullBottles;
      emptyBottles += fullBottles;
      fullBottles = 0;

      // Refiling bottles
      while(emptyBottles >= numExchange) {
        fullBottles++;
        emptyBottles -= numExchange;
        numExchange++;
      }
    }

    return drunkenBottles;
  }
};
