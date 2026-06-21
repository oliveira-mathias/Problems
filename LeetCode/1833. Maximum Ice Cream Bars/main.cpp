class Solution {
public:
    // Time: O(n + MAX_PRICE)
    // Space: O(MAX_PRICE)
    int maxIceCream(vector<int>& costs, int coins) {
        constexpr int MAX_PRICE = 100000;
        vector<int> priceToAmount (MAX_PRICE+1);

        // Counting sort
        for(int cost : costs) {
            priceToAmount[cost]++;
        }

        int bars = 0;
        for(int price=1; coins >= price && price<=MAX_PRICE; price++) {
            int toBuy = min(priceToAmount[price], coins/price);
            bars += toBuy;
            coins -= price*toBuy;
        }
        return bars;
    }
};
