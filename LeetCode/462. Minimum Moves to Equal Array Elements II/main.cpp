/*
    Explanation: Since we can increment or decrement single element, it means we can move such element freely, without any constraints.
    Let m be the target element to which we intend all the elements in nums to be equal.
    Then, we can see that we want to minimize T(m) = \sum{|nums[i] - m|}
    Since, the module function is convex, T(m) as a sum of module functions is also convex.
    This means that if we find a local minima for it, we found its global minima.

    By the simetry of the problem, two good guesses for optimal m are the median and the mean.
    Consider the array nums = [0,0,0,0,100] the mean is 20, so instead of making 100 walks down to 0 in 100 steps, by choosing m=mean(nums), T(m) = 4*20 + 80 = 160 > 100.
    So the answer can't be the mean because it is too sensitive to outliers. Clearly, we can modify slightly this example to yield a result as far from the optimal answer as we want.

    Consider m = median(nums).
    Clearly, the previous example doesn't break, because the median of such array is 0.
    Lets see that the median is indeed the answer.
    Assume n = nums.size() is odd.
    We prove T(m) is a local minima. Lets consider T(m+1), clearly by incrementing m, what happens is that floor(n/2) elements reduce 1 in the sum of T function, but floor(n/2) + 1 elements increase 1 in the sum. Thus, T(m+1) > T(m). Analogously, T(m-1) > T(m). This means m is a local minima, hence a global minima.
    When n is even, then there is not a median element. Lets call lowerMedian and upperMedian the two elements from nums used to compute the median of the array. Using an analogous argument, T(lowerMedian) = T(upperMedian). Using an analogous argument, we can see that T(lowerMedian-1) > T(lowerMedian) = T(upperMedian) < T(upperMedian + 1).
    By the symetry of the partitions [nums[0],..., loweMedian] and [upperMedian, ..., nums[n-1]], we can see that any element in the interval [lowerMedian, upperMedian] reaches the minimum of  the function T(m), but since m is an integer, we can take lowerMedian or upperMedian as the answer. Here we used again the convex function property. 
*/
class Solution {
public:
    // Time: O(n)
    // Space: O(1)
    int minMoves2(vector<int>& nums) {
        int n = nums.size();
        auto lowerMedianIt = nums.begin() + n/2;
        nth_element(nums.begin(), lowerMedianIt, nums.end());
        int moves = 0;
        for(int num : nums) {
            moves += abs(num - *lowerMedianIt);
        }
        return moves;
    }
};
