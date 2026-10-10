class Solution {
public:
    // Time: O(2^n) ~ This is a loose complexity
    // Space: O(target)
    vector<vector<int>> combinationSum(const vector<int>& candidates, int target) {
        vector<vector<int>> comb;
        const auto backtrack = [&comb, &candidates](this auto&& backtrack, vector<int>& currSol, int toGo, int start) -> void {
            // Base case
            if(toGo == 0) {
                comb.push_back(currSol);
                return;
            }

            // Recursive step
            for(int i=start; i<candidates.size(); ++i) {
                if(candidates[i] <= toGo) {
                    currSol.push_back(candidates[i]);
                    backtrack(currSol, toGo - candidates[i], i);
                    currSol.pop_back();
                }
            }
        };
        vector<int> currSol;
        backtrack(currSol, target, 0);
        return comb;
    }
};
