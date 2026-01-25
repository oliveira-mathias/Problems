//My strategy is to match the first with the last, the second with the second last and so on.

//Suppose the array A is sorted.

//Suppose that there is a optimal solution that agrees with my algorithm up to the point of associating A[i], with A[j], but it disagrees at this step, it matches A[j] with some A[i'] where i' > i. And that i is maximum about this property.

//Furthermore, suppose this optimal solution associates A[i] with some A[j'] where j' < j.

//Then, since the array is sorted, we can see that

//A[j] + A[i'] >= A[i] + A[j]
//A[j] + A[i'] >= A[i'] + A[j']

//The we can modify the optimal solution by matching A[i] with A[j] and A[i'] with A[j'] and still get an optimal solution. What contradicts the maximaliti if i.

class Solution {
public:
    // Time: O(n log(n))
    // Space: O(log(n))
    int minPairSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        int minimunMaxSum = nums.front() + nums.back();
        for(int l=0, r=nums.size()-1; l<r; ++l, --r) {
            minimunMaxSum = max(minimunMaxSum, nums[l] + nums[r]);
        }

        return minimunMaxSum;
    }
};
