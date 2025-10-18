class Solution {
public:
  int maxDistinctElements(vector<int>& nums, int k) {
    sort(nums.begin(), nums.end());

    // Basis step
    nums[nums.size()-1] = nums[nums.size()-1] + k;

    for(int i=nums.size()-2; i>=0; --i) {
      int gap = nums[i+1] - nums[i];

      int offset;
      if(gap > k) {
        offset = k;
      }
      else if(gap <= -k) {
        offset = -k;
      }
      else {
        offset = gap-1;
      }

      nums[i] += offset;
    }

    // Count uniques
    int uniques = 1;
    int lastSeen = nums[0];
    for(int i=1; i<nums.size(); ++i) {
      if(nums[i] != lastSeen) {
          uniques++;
      }
      lastSeen = nums[i];
    }

    return uniques;
  }
};
