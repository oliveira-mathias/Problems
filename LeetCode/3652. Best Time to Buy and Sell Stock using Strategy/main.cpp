class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    long long maxProfit(vector<int>& prices, vector<int>& strategy, int k) {
        int n = prices.size();
        
        // Assume n > 0
        // Sliding window part
        long long windowSum = 0;
        for(int i=0; i<k/2; ++i) {
            windowSum += prices[n -1 - i];
        }

        // Window is: back | [ ___ | windowSum] | front
        long long back = 0;
        for(int i=0; i<n-k; ++i) {
            back += prices[i]*strategy[i];
        }
        long long front = 0;
        long long maxSum = back + front;
        for(int i=n-k; i<n; ++i) {
            maxSum += prices[i]*strategy[i];
        }
        // i is the first element of the window
        for(int i = n-k; i >= 0; --i) {
            // Compute this window sum
            
            maxSum = max(maxSum, back + front + windowSum);

            // Updating window
            windowSum -= prices[i + k - 1];
            windowSum += prices[i + k/2 -1];
            back -= (i > 0) ? prices[i-1]*strategy[i-1] : 0;
            front += prices[i + k -1] * strategy[i + k -1];
        }
        return maxSum;
    }
};
