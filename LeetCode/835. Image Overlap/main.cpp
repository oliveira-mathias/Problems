class Solution {
public:
    // Time: O(n^4)
    // Space: O(1)
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        int n = img1.size();
        int maxOverlap = 0;
        // We use the convolution structure to structure the loop
        for(int i=0; i<2*n-1; ++i) {
            for(int j=0; j<2*n-1; ++j) {
                int img1XStart = max(n-1-i, 0);
                int img1Ystart = max(n-1-j, 0);

                int img2XStart = max(i-n+1, 0);
                int img2YStart = max(j-n+1, 0);
                int overlap = 0;
                for(int k=0; img1XStart+k<n && img2XStart+k<n; ++k) {
                    for(int l=0; img1Ystart+l<n && img2YStart+l<n; ++l) {
                        if(img1[img1XStart+k][img1Ystart+l] && img2[img2XStart+k][img2YStart+l]) {
                            overlap++;
                        }
                    }
                }
                maxOverlap = max(maxOverlap, overlap);
            }
        }
        return maxOverlap;
    }
};
