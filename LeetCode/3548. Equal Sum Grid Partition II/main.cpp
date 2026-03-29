class Solution {
public:
    // Time: O(mn)
    // Space: O(mn)
    bool canPartitionGrid(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Precomputing data
        unordered_map<long long, int> freq;
        long long totalSum = 0;
        for(int i=0; i<m; ++i) {
            for(int j=0; j<n; ++j) {
                totalSum += grid[i][j];
                freq[grid[i][j]]++;
            }
        }

        // Horizontal cut
        unordered_map<long long, int> partitionA = freq;
        unordered_map<long long, int> partitionB;
        long long partitionBSum = 0;
        for(int i=m-1; i>0; --i) {
            // Here we pass row i from partitionA to partitionB
            for(int j=0; j<n; ++j) {
                partitionA[grid[i][j]]--;
                partitionB[grid[i][j]]++;
                partitionBSum += grid[i][j];
            }

            long long partitionASum = totalSum - partitionBSum;
            if(partitionASum > partitionBSum) {
                // Handle the conectivity constraint
                long long delta = partitionASum - partitionBSum;
                if(grid[0][0] == delta || grid[0][n-1] == delta || grid[i-1][0] == delta || grid[i-1][n-1] == delta) return true;
                auto it = partitionA.find(delta);
                if(i > 1 && n > 1 && it != partitionA.end() && it->second) return true;
            }
            else if(partitionASum < partitionBSum) {
                long long delta = partitionBSum - partitionASum;
                if(grid[m-1][0] == delta || grid[m-1][n-1] == delta || grid[i][0] == delta || grid[i][n-1] == delta) return true;
                auto it = partitionB.find(delta);
                if(i < m-1 && n > 1 && it != partitionB.end() && it->second) return true;
            }
            else return true;
        }

        // Vertical cut
        partitionA = std::move(freq);
        partitionB.clear();
        partitionBSum = 0;
        for(int j=n-1; j>0; --j) {
            // Here we pass col j from partitionA to partitionB
            for(int i=0; i<m; ++i) {
                partitionA[grid[i][j]]--;
                partitionB[grid[i][j]]++;
                partitionBSum += grid[i][j];
            }

            long long partitionASum = totalSum - partitionBSum;
            if(partitionASum > partitionBSum) {
                // Handle the conectivity constraint
                long long delta = partitionASum - partitionBSum;
                if(grid[0][0] == delta || grid[m-1][0] == delta || grid[0][j-1] == delta || grid[m-1][j-1] == delta) return true;
                auto it = partitionA.find(delta);
                if(j > 1 && m > 1 && it != partitionA.end() && it->second) return true;
            }
            else if(partitionASum < partitionBSum) {
                long long delta = partitionBSum - partitionASum;
                if(grid[0][n-1] == delta || grid[m-1][n-1] == delta || grid[0][j] == delta || grid[m-1][j] == delta) return true;
                auto it = partitionB.find(delta);
                if(j < n-1 && m > 1 && it != partitionB.end() && it->second) return true;
            }
            else return true;
        }

        return false;
    }
};
